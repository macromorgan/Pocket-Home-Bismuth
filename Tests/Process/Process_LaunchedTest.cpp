#include "Process_Launched.h"
#include "Process_Launcher.h"
#include "WindowFocus.h"
#include "XWindowInterface.h"
#include "DelayUtils.h"
#include "SystemCommands.h"
#include "JuceHeader.h"
#include <map>

/* Simple commands to run, paired with expected output: */
static const std::map<juce::String, juce::String> outputCommands =
{
    {"echo (test)", "(test)"},
    {"expr 1 + 1", "2"},
};

/* Terminal applications to try running: */
static const juce::StringArray termApps =
{
    "top",
    "vi"
};

/* Simple windowed applications to try running: */
static const juce::StringArray windowedApps = 
{
    "xclock",
    "xeyes"
};

namespace Process { class LaunchedTest; }

class Process::LaunchedTest : public juce::UnitTest
{
public:
    LaunchedTest() : juce::UnitTest("Process::Launched testing", "Process") {}
    
    void runTest() override
    {
        using juce::String;
        String output;
        SystemCommands commandReader;

        beginTest("Process output test");
        for(auto& iter : outputCommands)
        {
            String command = iter.first;
            String expectedResult = iter.second;
            String commandName = command.initialSectionNotContaining(" ");
            if(Launcher::testCommand(commandName))
            {
                Launched outputProcess(command);
                outputProcess.waitForProcessToFinish(1000);
                expect(!outputProcess.isRunning(), String("\"")
                        + commandName 
                        + "\" process still running, but should be finished.");
                String output = outputProcess.getProcessOutput().trim();
                expectEquals(output, expectedResult, String("\"") + commandName
                        + "\" process output was incorrect.");
                expect(!outputProcess.kill(),
                        "Kill command returned true, invalid if finished");
            }
            else
            {
                logMessage(String("Command \"") + commandName
                        + "\" doesn't appear to be valid, skipping test.");
            }
        }
        
        beginTest("Terminal application test");
        for(const String& command : termApps)
        {
            if(Launcher::testCommand(command))
            {
                Launched termProcess(command);
                expect(DelayUtils::idleUntil([&termProcess]()
                { 
                    return termProcess.isRunning(); 
                }, 500, 5000), String("\"") + command 
                        + "\" process is not running.");
                output = termProcess.getProcessOutput();
                expect(output.isEmpty(), String("Unexpected process output ") 
                        + output);
                expect(termProcess.kill(), "Failed to kill process.");
            }
            else
            {
                logMessage(String("Command \"") + command
                        + "\" doesn't appear to be valid, skipping test.");
            }
        }
        
        beginTest("Invalid command handling test");
        String badCommand("DefinitelyNotAValidLaunchCommand");
        expect(!Launcher::testCommand(badCommand),
                "DefinitelyNotAValidLaunchCommand should have been invalid.");
        Launched bad("DefinitelyNotAValidLaunchCommand");
        expect(!DelayUtils::idleUntil([&bad]() { return bad.isRunning(); },
                200, 2000), "Process running despite bad launch command.");
        output = bad.getProcessOutput();
        expectEquals(String(), output,
                "Bad process should have had no output.");
        expectEquals(String(bad.getExitCode()), String("0"),
			"Bad process error code should have been 0.");
        
        beginTest("Windowed launch and activation test");
        for(const String& command : windowedApps)
        {
            if(Launcher::testCommand(command))
            {
                Launched windowedApp(command);
                expect(DelayUtils::idleUntil([&windowedApp]()
                { 
                    return windowedApp.isRunning(); 
                }, 100, 1000), String("\"") + command
                        + "\" process not is running.");
                windowedApp.activateWindow();
                expect(DelayUtils::idleUntil(
                        []() { return !WindowFocus::isFocused(); }, 500, 8000),
                        "pocket-home window should not be focused.");
                windowedApp.kill();
                XWindowInterface xwin;
                xwin.activateWindow(xwin.getPocketHomeWindow());
                expect(!windowedApp.isRunning(), String("\"") + command
                        + "\" process should be dead.");
            }
            else
            {
                logMessage(String("Command \"") + command
                        + "\" doesn't appear to be valid, skipping test.");
            }
        }
    }
};

static Process::LaunchedTest test;

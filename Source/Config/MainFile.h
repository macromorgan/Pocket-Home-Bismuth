#pragma once
/**
 * @file Config/MainFile.h
 * 
 * @brief Loads general application settings from the config.json file.
 */

#include "Config/FileHandler.h"
#include "Config/Listener.h"

namespace Config { class MainFile; }
namespace Config { class MainResource; }
namespace Config { class MainListener; }

class Config::MainFile : private Config::FileHandler<MainResource>
{
public:
    MainFile();

    virtual ~MainFile() { }

    /**
     * @brief  Gets how frequently the Wifi settings page should scan for
     *         access point updates.
     *
     * @return   The update frequency, in milliseconds.
     */
    int getWifiScanFrequency() const;

    /**
     * @brief  Gets the HomePage background image or color.
     *
     * @return  The background to display behind the HomePage component. 
     */
    juce::String getHomeBackground() const;

    /**
     * @brief  Gets the prefix to place before system commands when they should
     *         be launched within a new terminal window.
     *
     * @return  The command prefix, usually something like 'terminal -e'.
     */
    juce::String getTermLaunchPrefix() const;

    /**
     * @brief  Gets the Wifi interface to use when managing Wifi connections.
     *
     * @return  The name of a Wifi interface that should override the default
     *          choice.
     */
    juce::String getWifiInterface() const;

    /**
     * @brief  Gets if the mouse cursor should be shown when pocket-home is
     *         active.
     *
     * @return  Whether the cursor should be shown. 
     */
    bool getShowCursor() const;

    /**
     * @brief  Gets if the clock will be shown within the HomePage component.
     *
     * @return  Whether the clock label should be shown. 
     */
    bool getShowClock() const;

    /**
     * @brief  Gets if the clock label will show time in 24 hour mode, or in 
     *         12 hour AM/PM mode.
     *
     * @return  True if 24 hour mode should be used, false if 12 hour mode
     *          should be used.
     */
    bool get24HourEnabled() const;

    /**
     * @brief  Sets if the mouse cursor is shown or hidden.
     *
     * @param showCursor  Whether the mouse cursor will be shown.
     */
    void setShowCursor(const bool showCursor);

    /**
     * @brief  Sets if the clock label is shown or hidden.
     *
     * @param showClock  Whether the clock label will be shown.
     */
    void setShowClock(const bool showClock);

    /**
     * @brief  Sets if the clock label will use 24 hour mode.
     *
     * @param use24HourMode  Whether the clock label should use 24 hour mode
     *                       instead of 12 hour mode.
     */
    void set24HourEnabled(const bool use24HourMode);
};

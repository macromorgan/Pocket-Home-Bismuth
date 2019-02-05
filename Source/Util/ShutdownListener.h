#pragma once
/**
 * @file  ShutdownListener.h
 *
 * @brief  Provides a notification system for classes that need to perform 
 *         specific actions when the program is about to shut down.
 */

#include "JuceHeader.h"

/**
 * @brief  Receives a notification callback when the application is about to 
 *         shut down. 
 */
class ShutdownListener
{
public:
    /**
     * @brief  Registers the listener to receive shutdown messages.
     */
    ShutdownListener();

    /**
     * @brief  Unregisters the listener from shutdown messages.
     */
    virtual ~ShutdownListener();

private:
    /* Shutdown messages may only be sent through ShutdownBroadcaster. */
    friend class ShutdownBroadcaster;

    /**
     * @brief  The callback function that will run when the program is about
     *         to shut down.
     */
    virtual void onShutdown() = 0;

    /* Keeps the ShutdownListener from being destroyed as it receives a
       notification: */
    juce::CriticalSection notifyGuard;
};

/**
 * @brief  Provides the static method that the application class uses to send
 *         the shutdown message.
 */
class ShutdownBroadcaster
{
private:
    /* Only the main application class may send shutdown messages. */
    friend class PocketHomeApplication;

    /**
     * @brief  Sends the shutdown message to all shutdown listeners.
     */
    static void broadcastShutdown();
};

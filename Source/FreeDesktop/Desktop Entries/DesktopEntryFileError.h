#pragma once
#include <exception>
#include "JuceHeader.h"

/**
 * @file  DesktopEntryFileError.h
 *
 * @brief  Signals that a desktop entry file is invalid.
 */
struct DesktopEntryFileError : public std::exception
{
public:
    /**
     * @brief  Creates a new exception for an invalid desktop entry file.
     *
     * @param file   The invalid file being read.
     *
     * @param error  A brief description of the problem encountered.
     */
    DesktopEntryFileError(const juce::File& file, const juce::String& error) :
            errorMessage(file.getFullPathName() + ": " + error) { }

    /**
     * @brief  Gets a string describing the error.
     *
     * @return  A string containing the file's path and a short description
     *          of the file error.
     */
    virtual const char* what() const noexcept override
    {
        return errorMessage.toRawUTF8();
    }

private:
    juce::String errorMessage;
};

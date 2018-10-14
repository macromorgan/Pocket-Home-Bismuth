#pragma once
#include "ConfigFile.h"
#include "AppJSON.h"
#include "AppMenuItem.h"

/**
 * @file AppConfigFile.h
 * 
 * @brief  Reads and edits the tree of pinned application shortcuts and folders 
 *         displayed in the AppMenuComponent.
 *
 * The apps.json file defines a tree of menu items.  Each menu item can hold 
 * either an application launch command, or a list of other menu items and
 * application categories to show in a new menu folder.  All menu items have a
 * displayed title and icon.
 *
 * AppConfigFile uses this JSON menu data to construct the AppMenuItem objects
 * used to build the AppMenuComponent.  It also provides an interface for 
 * adding, editing, or removing menu data from the JSON file.
 * 
 * @see  AppMenuComponent.h
 */

class AppConfigFile : public ConfigFile<AppJSON>
{
public:
    AppConfigFile() { }

    virtual ~AppConfigFile() { }
    
    /**
     * @brief  Gets a menu item representing the root folder of the application
     *         menu.
     *
     * @return  A folder menu item holding the top level of the application
     *          menu tree.
     */
    AppMenuItem getRootFolderItem();

    /**
     * @brief  Adds a new menu item to the list of menu items.
     *
     * @param title            The title to print on the menu item.
     *
     * @param icon             The name or path of the menu item's icon.
     *
     * @param command          The menu item's application launch command, or 
     *                         the empty string if the menu item does not launch 
     *                         an application.
     *
     * @param launchInTerm     Whether the menu item launches an application
     *                         within a new terminal window.
     * 
     * @param categories       A list of application categories associated with
     *                         the menu item.
     * 
     * @param parentFolder     The parent folder item the new menu item will be
     *                         inserted into.
     *
     * @param index            The index where the menu item will be inserted
     *                         into the parent folder.
     *
     * @return                 The created menu item, or a null menu item if
     *                         creating the menu item failed.
     */
    AppMenuItem addMenuItem(
            const juce::String& title, 
            const juce::String& icon,
            const juce::String& command,
            const bool launchInTerm,
            const juce::StringArray& categories,
            AppMenuItem& parentFolder,
            const int index);
};

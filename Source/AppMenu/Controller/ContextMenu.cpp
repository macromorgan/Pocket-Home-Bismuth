#define APPMENU_IMPLEMENTATION_ONLY
#include "AppMenu/MenuData/ConfigFile.h"
#include "AppMenu/Editors/ExistingItemEditor.h"
#include "AppMenu/Editors/NewConfigItemEditor.h"
#include "AppMenu/Editors/NewDesktopAppEditor.h"
#include "ContextMenu.h"

/* Localized text keys: */
static const constexpr char* localeTextKey      = "AppMenu::ContextMenu";
static const constexpr char* editTextKey        = "edit_app";
static const constexpr char* deleteTextKey      = "delete_app";
static const constexpr char* pinItemTextKey     = "add_shortcut";
static const constexpr char* moveBackTextKey    = "move_back";
static const constexpr char* moveForwardTextKey = "move_forward";
static const constexpr char* newShortcutTextKey = "new_shortcut";
static const constexpr char* newEntryTextKey    = "new_entry";
static const constexpr char* newFolderTextKey   = "new_folder";

/* Menu option codes: */
enum class OptionCode
{
    Edit = 1,
    Delete,
    NewShortcut,
    NewFolder,
    NewDesktopEntry,
    PinToRoot,
    MoveBack,
    MoveForward
};

AppMenu::ContextMenu::ContextMenu() : Localized(localeTextKey) { }

/*
 * Sets popup menu options for editing a menu item.
 */
void AppMenu::ContextMenu::setMenuItemOptions(MenuItem menuItem)
{
    if(menuItem.isNull())
    {
        // The menu item parameter should never be null.
        jassertfalse;
        setGenericOptions();
        return;
    }
    clear();
    editedItem = menuItem;
    insertIndex = 0;

    addItem(int(OptionCode::Edit), localeText(editTextKey));
    addItem(int(OptionCode::Delete), localeText(deleteTextKey));
    MenuItem parent = menuItem.getParentFolder();

    // The menu item parameter should always have a valid parent and index.
    jassert(menuItem.getIndex() >= 0);
    jassert(!parent.isNull());

    if(!parent.getParentFolder().isNull())
    {
        addItem(int(OptionCode::PinToRoot), localeText(pinItemTextKey));
    }
    if(menuItem.isFolder())
    {
        addItem(int(OptionCode::NewShortcut), localeText(newShortcutTextKey));
    }

    int lastMovableIndex = parent.getMovableChildCount() - 1;
    if(menuItem.getIndex() <= lastMovableIndex)
    {
        addItem(int(OptionCode::MoveBack), localeText(moveBackTextKey));
        if(menuItem.getIndex() != lastMovableIndex)
        {
            addItem(int(OptionCode::MoveForward), 
                    localeText(moveForwardTextKey));
        }
    }
}

/*
 * Set popup menu options for editing an open folder.
 */
void AppMenu::ContextMenu::setFolderOptions
(MenuItem folderItem, const int insertIndex)
{
    if(folderItem.isNull())
    {
        // The menu item parameter should never be null.
        jassertfalse;
        setGenericOptions();
        return;
    }
    clear();
    editedItem = folderItem;
    this->insertIndex = insertIndex;
    addItem(int(OptionCode::NewShortcut), localeText(newShortcutTextKey));
    addItem(int(OptionCode::NewFolder), localeText(newFolderTextKey));
}

/*
 * Set generic popup menu options, when no specific folder or menu
 *         item is clicked or selected.
 */
void AppMenu::ContextMenu::setGenericOptions()
{
    ConfigFile appConfig;
    clear();
    editedItem = appConfig.getRootFolderItem();
    insertIndex = 0;
    addItem(int(OptionCode::NewShortcut), localeText(newShortcutTextKey));
    addItem(int(OptionCode::NewFolder), localeText(newFolderTextKey));
    addItem(int(OptionCode::NewDesktopEntry), localeText(newEntryTextKey));
}

/**
 * @brief  Shows the popup menu, and handles the user's selection.
 */
void AppMenu::ContextMenu::showAndHandleSelection()
{
    const OptionCode selectedOption = (OptionCode) show();
    switch(selectedOption)
    {
        case OptionCode::Edit:
            jassert(!editedItem.isNull());
            break;
        case OptionCode::Delete:
            break;
        case OptionCode::PinToRoot:
            break;
        case OptionCode::MoveBack:
            break;
        case OptionCode::MoveForward:
            break;
        case OptionCode::NewShortcut:
            break;
        case OptionCode::NewFolder:
            break;
        case OptionCode::NewDesktopEntry:
            break;
        default:
            DBG("AppMenu::ContextMenu::" << __func__ 
                    << ": Unhandled menu option " << int(selectedOption));
            jassertfalse;
    }
}

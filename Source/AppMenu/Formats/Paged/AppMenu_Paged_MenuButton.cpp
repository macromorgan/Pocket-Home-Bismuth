#define APPMENU_IMPLEMENTATION
#include "AppMenu_Paged_MenuButton.h"
#include "AppMenu_MenuButton.h"
#include "Layout_Component_ConfigFile.h"

/*
 * Creates a new MenuButton component for a menu item.
 */
AppMenu::Paged::MenuButton::MenuButton(MenuItem menuItem) :
AppMenu::MenuButton(menuItem) { } 

/*
 * Finds the area relative to the menu button's bounds where the title should be
 * drawn.
 */
juce::Rectangle<float> AppMenu::Paged::MenuButton::findTitleBounds() const 
{
    using namespace Layout::Component;
    ConfigFile config;
    const int textHeight = config.getFontHeight(TextSize::smallText); 
    return getLocalBounds().withTop(getHeight() - textHeight).toFloat();
}

/*
 * Finds the area relative to the menu button's bounds where the icon should be 
 * drawn.
 */
juce::Rectangle<float> AppMenu::Paged::MenuButton::findIconBounds() const 
{
    using namespace Layout::Component;
    ConfigFile config;
    const int textHeight = config.getFontHeight(TextSize::smallText); 
    const int iconSize = std::min(getHeight() - textHeight, getWidth());
    return juce::Rectangle<float>((getWidth() - iconSize) / 2, 0,
            iconSize, iconSize);
}

/*
 * Checks if this button will draw an outline around its border.
 */
bool AppMenu::Paged::MenuButton::shouldDrawBorder() const 
{
    return isSelected();
}

/*
 * Checks if this button will fill in its background with its background color.
 */
bool AppMenu::Paged::MenuButton::shouldFillBackground() const 
{
    return true;
    //return isSelected();
}

/*
 * Gets the text justification of the button title.
 */
juce::Justification AppMenu::Paged::MenuButton::getTextJustification() const 
{
    return juce::Justification::centred;
}

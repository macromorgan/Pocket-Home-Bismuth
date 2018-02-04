#pragma once
/**
 * @file ScrollingMenuButton.h
 * 
 * ScrollingMenuButton is an AppMenuButton that is drawn for a ScrollingAppMenu
 */

#include "../AppMenuButton.h"

class ScrollingMenuButton : public AppMenuButton,
public ConfigurableComponent {
public:
    
    typedef ReferenceCountedObjectPtr<ScrollingMenuButton> Ptr;
    ScrollingMenuButton(AppMenuItem* menuItem,IconThread& iconThread,
            int columnIndex,int rowIndex, String name=String());
    virtual ~ScrollingMenuButton();
private:

    /**
     * Custom button painting method.
     */
    void paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown);


    /**
     * Re-calculates draw values whenever the button is resized
     */
    void resized() override;

    /**
     * Load button colors from configuration files.
     * @param assetNames is ignored, this component has no configurable
     * image asset.
     * @param colours
     */
    virtual void applyConfigAssets(Array<String> assetNames,
            Array<Colour> colours);

    //bounds for drawing app/folder name
    Rectangle<float> textBox;
    //bounds for drawing button icon
    Rectangle<float> imageBox;
    //font for drawing app/folder name
    Font titleFont;
    //Button text color
    Colour textColour;
    //Button background fill color, if not selected.
    Colour fillColour;
    //Button background fill color, if selected.
    Colour selectedFillColour;
    int columnIndex;
    int rowIndex;
};

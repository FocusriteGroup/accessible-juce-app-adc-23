
#include "Button.h"
#include <juce_gui_basics/detail/juce_ButtonAccessibilityHandler.h>

std::unique_ptr<juce::AccessibilityHandler> Button::createAccessibilityHandler ()
{
    return std::make_unique<juce::detail::ButtonAccessibilityHandler> (*this,
                                                                       isToggleable ()
                                                                           ? juce::AccessibilityRole::toggleButton
                                                                           : juce::AccessibilityRole::button);
}

bool Button::keyPressed (const juce::KeyPress & key)
{
    if (! isEnabled ())
        return false;

    if (key == juce::KeyPress::returnKey || key == juce::KeyPress::spaceKey)
    {
        triggerClick ();
        return true;
    }

    return false;
}

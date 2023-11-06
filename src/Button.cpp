
#include "Button.h"
#include <juce_gui_basics/detail/juce_ButtonAccessibilityHandler.h>

std::unique_ptr<juce::AccessibilityHandler> Button::createAccessibilityHandler ()
{
    return std::make_unique<juce::detail::ButtonAccessibilityHandler> (*this,
                                                                       isToggleable ()
                                                                           ? juce::AccessibilityRole::toggleButton
                                                                           : juce::AccessibilityRole::button);
}

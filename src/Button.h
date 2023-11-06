#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Button : public juce::TextButton
{
public:
    using TextButton::TextButton;

private:
    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler () override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Button)
};

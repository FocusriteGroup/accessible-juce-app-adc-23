#pragma once

#include <Button.h>
#include <juce_gui_basics/detail/juce_ButtonAccessibilityHandler.h>
#include <juce_gui_basics/juce_gui_basics.h>

class ChannelStrip : public juce::Component
{
public:
    ChannelStrip ();

    void resized () override;
    void paint (juce::Graphics & g) override;

private:
    Button muteButton {"M"};
    Button soloButton {"S"};
    Button phantomPowerButton {"48V"};

    juce::Slider levelSlider {juce::Slider::SliderStyle::LinearVertical,
                              juce::Slider::TextEntryBoxPosition::TextBoxBelow};

    juce::Slider gainRotary {juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                             juce::Slider::TextEntryBoxPosition::TextBoxBelow};

    juce::Slider panRotary {juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                            juce::Slider::TextEntryBoxPosition::TextBoxBelow};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStrip)
};

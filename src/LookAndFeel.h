#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    LookAndFeel ();

    void drawLinearSlider (juce::Graphics &,
                           int x,
                           int y,
                           int width,
                           int height,
                           float sliderPos,
                           float minSliderPos,
                           float maxSliderPos,
                           const juce::Slider::SliderStyle,
                           juce::Slider &) override;

    void drawRotarySlider (juce::Graphics & g,
                           int x,
                           int y,
                           int width,
                           int height,
                           float sliderPos,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider & slider) override;
};

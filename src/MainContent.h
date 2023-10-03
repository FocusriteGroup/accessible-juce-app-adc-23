#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <channel-strip/ChannelStripGroup.h>

class MainContent final : public juce::Component
{
public:
    MainContent ();
    ~MainContent () override = default;

private:
    void resized () override;
    void paint (juce::Graphics & g) override;

    ChannelStripGroup channelStrips;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

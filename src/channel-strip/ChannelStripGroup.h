#pragma once

#include "ChannelStrip.h"
#include <juce_gui_basics/juce_gui_basics.h>

class ChannelStripGroup : public juce::Component
{
public:
    ChannelStripGroup ();

    void resized () override;

private:
    std::array<ChannelStrip, 4> channelStrips;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripGroup)
};

#include "ChannelStripGroup.h"

ChannelStripGroup::ChannelStripGroup ()
{
    for (auto & channelStrip : channelStrips)
        addAndMakeVisible (channelStrip);
}

void ChannelStripGroup::resized ()
{
    juce::FlexBox mainFlex;
    mainFlex.flexDirection = juce::FlexBox::Direction::row;
    mainFlex.justifyContent = juce::FlexBox::JustifyContent::center;

    for (auto & channelStrip : channelStrips)
    {
        mainFlex.items.add (
            juce::FlexItem {channelStrip}.withMargin (5.0f).withMinWidth (150.0f).withMinHeight (400.0f));
    }

    const juce::BorderSize margin {25, 0, 25, 0};
    mainFlex.performLayout (margin.subtractedFrom (getLocalBounds ()));
}

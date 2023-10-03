#include "MainContent.h"

MainContent::MainContent ()
{
    static constexpr auto width = 720;
    static constexpr auto height = 450;
    setSize (width, height);

    addAndMakeVisible (channelStrips);
}

void MainContent::resized ()
{
    channelStrips.setBounds (getLocalBounds ());
}

void MainContent::paint (juce::Graphics & g)
{
    g.fillAll (getLookAndFeel ().findColour (juce::ResizableWindow::backgroundColourId));
}

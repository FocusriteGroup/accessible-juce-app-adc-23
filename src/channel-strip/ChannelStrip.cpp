#include "ChannelStrip.h"

static void setUpPanControl (juce::Slider & slider)
{
    slider.setRange (juce::Range {-100.0, 100.0}, 1.0);
    slider.textFromValueFunction = [] (double value)
    {
        const juce::String valueText {value};
        const juce::String suffix = value < 0 ? "% L" : "% R";
        return value == 0.0 ? "C" : valueText.removeCharacters ({"-"}) + suffix;
    };
    slider.updateText ();
    slider.setDoubleClickReturnValue (true, 0.0);
    slider.setTextBoxIsEditable (false);
    slider.setTitle ("Pan");
}

static void setUpGainControl (juce::Slider & slider)
{
    slider.setRange (juce::Range {0.0, 70.0}, 10.0);
    slider.setTextValueSuffix ("dB");
    slider.setDoubleClickReturnValue (true, 0.0);
    slider.setTextBoxIsEditable (false);
    slider.setTitle ("Gain");
}

static void setUpLevelControl (juce::Slider & slider)
{
    slider.setRange (juce::Range {-128.0, 0.0}, 1.0);
    slider.setTextValueSuffix ("dB");
    slider.setDoubleClickReturnValue (true, 0.0);
    slider.setTextBoxIsEditable (false);
    slider.setTitle ("Level");
}

ChannelStrip::ChannelStrip ()
{
    setFocusContainerType (FocusContainerType::focusContainer);

    muteButton.setClickingTogglesState (true);
    muteButton.setTitle ("Mute");
    addAndMakeVisible (muteButton);

    soloButton.setClickingTogglesState (true);
    soloButton.setTitle ("Solo");
    addAndMakeVisible (soloButton);

    phantomPowerButton.setClickingTogglesState (true);
    phantomPowerButton.setTitle ("48V");
    addAndMakeVisible (phantomPowerButton);

    setUpPanControl (panRotary);
    addAndMakeVisible (panRotary);

    setUpGainControl (gainRotary);
    addAndMakeVisible (gainRotary);

    setUpLevelControl (levelSlider);
    addAndMakeVisible (levelSlider);
}

static auto createButtonGridItem (juce::TextButton & button)
{
    const auto height = juce::Font {}.getHeight () * 2.0f;
    const auto width = static_cast<float> (
        button.getLookAndFeel ().getTextButtonWidthToFitText (button, static_cast<int> (height)));

    return juce::GridItem {button}.withWidth (width).withHeight (height);
}

static auto createRotaryGridItem (juce::Slider & rotarySlider)
{
    juce::GridItem item {rotarySlider};
    item.minHeight = 70.0f;
    return item;
}

void ChannelStrip::resized ()
{
    juce::Grid mainGrid;
    mainGrid.templateColumns = {juce::Grid::Fr (1), juce::Grid::Fr (1)};
    mainGrid.templateRows = {juce::Grid::Fr (1), juce::Grid::Fr (1), juce::Grid::Fr (4), juce::Grid::Fr (1)};
    mainGrid.rowGap = juce::Grid::Px {15};
    mainGrid.columnGap = juce::Grid::Px {15};
    mainGrid.justifyItems = juce::Grid::JustifyItems::center;
    mainGrid.alignItems = juce::Grid::AlignItems::center;

    static constexpr auto sliderWidth = 50.0f;

    mainGrid.items = {createButtonGridItem (phantomPowerButton),
                      createRotaryGridItem (gainRotary).withWidth (sliderWidth),
                      createRotaryGridItem (panRotary)
                          .withWidth (sliderWidth)
                          .withArea ({}, juce::GridItem::Span {mainGrid.getNumberOfColumns ()}),
                      juce::GridItem (levelSlider)
                          .withWidth (sliderWidth)
                          .withArea ({}, juce::GridItem::Span {mainGrid.getNumberOfColumns ()}),
                      createButtonGridItem (muteButton).withAlignSelf (juce::GridItem::AlignSelf::start),
                      createButtonGridItem (soloButton).withAlignSelf (juce::GridItem::AlignSelf::start)};

    const juce::BorderSize margin {10};
    mainGrid.performLayout (margin.subtractedFrom (getLocalBounds ()));
}

void ChannelStrip::paint (juce::Graphics & g)
{
    g.setColour (findColour (juce::Slider::trackColourId));

    static constexpr auto cornerRadius = 20.0f;
    static constexpr auto borderThickness = 1.0f;

    g.drawRoundedRectangle (getLocalBounds ().toFloat ().reduced (borderThickness / 2.0f),
                            cornerRadius,
                            borderThickness);
}

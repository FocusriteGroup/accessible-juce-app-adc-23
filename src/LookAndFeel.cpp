#include "LookAndFeel.h"

[[nodiscard]] static auto fromHex (const juce::String & hex)
{
    return juce::Colour::fromString (hex.replace ("#", "").paddedLeft ('F', 8));
}

LookAndFeel::LookAndFeel ()
{
    const auto neutral1 = fromHex ("#FBFBFD");
    const auto neutral2 = fromHex ("#8D8D92");
    const auto neutral3 = fromHex ("#4D4D53");

    setColour (juce::ResizableWindow::backgroundColourId, neutral1);

    setColour (juce::TextButton::buttonColourId, neutral1);
    setColour (juce::TextButton::textColourOffId, neutral3);

    setColour (juce::ComboBox::outlineColourId, neutral2);
    setColour (juce::Slider::rotarySliderOutlineColourId, neutral2);
    setColour (juce::Slider::textBoxOutlineColourId, neutral2);

    setColour (juce::TextButton::buttonOnColourId, neutral3);
    setColour (juce::TextButton::textColourOnId, neutral1);

    setColour (juce::Slider::thumbColourId, neutral1);

    setColour (juce::Slider::rotarySliderFillColourId, neutral3);
    setColour (juce::Slider::trackColourId, neutral3);

    setColour (juce::Slider::textBoxTextColourId, neutral3);
}

static void drawSliderHandle (juce::Graphics & g, const juce::Slider & slider, juce::Rectangle<float> bounds)
{
    auto fillColour = slider.findColour (juce::Slider::thumbColourId);

    if (slider.isMouseOverOrDragging ())
        fillColour = fillColour.contrasting (slider.isMouseButtonDown () ? 0.2f : 0.05f);

    g.setColour (fillColour);
    g.fillEllipse (bounds);

    g.setColour (slider.findColour (juce::Slider::rotarySliderOutlineColourId));
    g.drawEllipse (bounds, 1.0f);
}

void LookAndFeel::drawLinearSlider (juce::Graphics & g,
                                    int x,
                                    int y,
                                    int width,
                                    int height,
                                    float sliderPos,
                                    float /*minSliderPos*/,
                                    float /*maxSliderPos*/,
                                    const juce::Slider::SliderStyle /*sliderStyle*/,
                                    juce::Slider & slider)
{
    const auto trackWidth = juce::jmin (8.0f, width * 0.25f);

    const juce::Rectangle<int> outlineArea {(x + width / 2) - static_cast<int> (trackWidth) / 2,
                                            y,
                                            static_cast<int> (trackWidth),
                                            height};
    g.setColour (slider.findColour (juce::Slider::rotarySliderOutlineColourId));
    g.drawRect (outlineArea, 1.0f);

    const auto fillLineX = static_cast<float> (x) + static_cast<float> (width) * 0.5f;
    const juce::Line<float> fillLine {{fillLineX, sliderPos},
                                      {fillLineX, static_cast<float> (y + height)}};
    g.setColour (slider.findColour (juce::Slider::trackColourId));
    g.drawLine (fillLine, trackWidth);

    const auto handleWidth = trackWidth * 2.3f;
    const auto handleBounds = juce::Rectangle (handleWidth, handleWidth).withCentre ({fillLineX, sliderPos});
    drawSliderHandle (g, slider, handleBounds);
}

static juce::Path generateValueArc (const juce::Slider & slider,
                                    juce::Rectangle<float> bounds,
                                    float radius,
                                    float startAngle,
                                    float endAngle)
{
    const auto isCentred = slider.getDoubleClickReturnValue () > slider.getRange ().getStart ();

    juce::Path arc;
    arc.addCentredArc (bounds.getCentreX (),
                       bounds.getCentreY (),
                       radius,
                       radius,
                       0.0f,
                       isCentred ? juce::MathConstants<float>::twoPi : startAngle,
                       endAngle,
                       true);

    return arc;
}

static juce::Line<float> getLineBetweenArcs (juce::Point<float> pos,
                                             float innerArcRadius,
                                             float outerArcRadius,
                                             float angleAlongArcs)
{
    static constexpr auto halfPi = juce::MathConstants<float>::halfPi;

    juce::Point start {pos.getX () + outerArcRadius * std::cos (angleAlongArcs - halfPi),
                       pos.getY () + outerArcRadius * std::sin (angleAlongArcs - halfPi)};

    juce::Point end {pos.getX () + innerArcRadius * std::cos (angleAlongArcs - halfPi),
                     pos.getY () + innerArcRadius * std::sin (angleAlongArcs - halfPi)};

    return {start, end};
}

static juce::Path generateOutlineArc (juce::Rectangle<float> bounds,
                                      float radius,
                                      float trackWidth,
                                      float startAngle,
                                      float endAngle)
{
    const auto innerArcRadius = radius - trackWidth / 2.0f;
    const auto outerArcRadius = radius + trackWidth / 2.0f;

    juce::Path path;
    path.addCentredArc (bounds.getCentreX (),
                        bounds.getCentreY (),
                        innerArcRadius,
                        innerArcRadius,
                        0.0f,
                        startAngle,
                        endAngle,
                        true);
    path.addCentredArc (bounds.getCentreX (),
                        bounds.getCentreY (),
                        outerArcRadius,
                        outerArcRadius,
                        0.0f,
                        startAngle,
                        endAngle,
                        true);

    path.addLineSegment (getLineBetweenArcs (bounds.getCentre (), innerArcRadius, outerArcRadius, startAngle),
                         0.0f);

    path.addLineSegment (getLineBetweenArcs (bounds.getCentre (), innerArcRadius, outerArcRadius, endAngle),
                         0.0f);

    return path;
}

void LookAndFeel::drawRotarySlider (juce::Graphics & g,
                                    int x,
                                    int y,
                                    int width,
                                    int height,
                                    float sliderPos,
                                    float rotaryStartAngle,
                                    float rotaryEndAngle,
                                    juce::Slider & slider)
{
    auto bounds = juce::Rectangle<int> {x, y, width, height}.toFloat ().reduced (10);

    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const auto radius = juce::jmin (bounds.getWidth (), bounds.getHeight ()) / 2.0f;

    const auto trackWidth = juce::jmin (8.0f, radius * 0.5f);
    const auto arcRadius = radius - trackWidth * 0.5f;

    g.setColour (slider.findColour (juce::Slider::rotarySliderOutlineColourId));
    g.strokePath (generateOutlineArc (bounds, arcRadius, trackWidth, rotaryStartAngle, rotaryEndAngle),
                  juce::PathStrokeType (1.0f));

    g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId));
    g.strokePath (generateValueArc (slider, bounds, arcRadius, rotaryStartAngle, toAngle),
                  juce::PathStrokeType (trackWidth));

    const auto handleWidth = trackWidth * 2.3f;
    const juce::Point handlePos {bounds.getCentreX () +
                                     arcRadius * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                                 bounds.getCentreY () +
                                     arcRadius * std::sin (toAngle - juce::MathConstants<float>::halfPi)};

    const auto handleBounds = juce::Rectangle<float> (handleWidth, handleWidth).withCentre (handlePos);
    drawSliderHandle (g, slider, handleBounds);
}

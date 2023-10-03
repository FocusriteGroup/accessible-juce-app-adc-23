#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class ExplicitFocusOrder
{
public:
    static ExplicitFocusOrder startingWith (juce::Component & component)
    {
        return ExplicitFocusOrder {}.then (component);
    }

    ExplicitFocusOrder & then (juce::Component & component)
    {
        component.setExplicitFocusOrder (index);
        index += 1;

        return *this;
    }

private:
    ExplicitFocusOrder () = default;
    ExplicitFocusOrder (const ExplicitFocusOrder &) = default;
    ExplicitFocusOrder & operator= (const ExplicitFocusOrder &) = delete;
    ExplicitFocusOrder (ExplicitFocusOrder &&) = delete;
    ExplicitFocusOrder & operator= (ExplicitFocusOrder &&) = delete;

    int index {1};
};

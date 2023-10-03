#pragma once

#include "LookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>

class Application final : public juce::JUCEApplication
{
public:
    Application ();

private:
    const juce::String getApplicationName () override;
    const juce::String getApplicationVersion () override;

    void initialise (const juce::String & commandLineArguments) override;
    void shutdown () override;
    void systemRequestedQuit () override;
    bool moreThanOneInstanceAllowed () override;

    LookAndFeel lookAndFeel;

    class Window;
    std::unique_ptr<Window> window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Application)
};

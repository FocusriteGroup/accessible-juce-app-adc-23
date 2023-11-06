#include "Application.h"
#include "MainContent.h"

Application::Application () = default;

const juce::String Application::getApplicationName ()
{
    return JUCE_APPLICATION_NAME_STRING;
}

const juce::String Application::getApplicationVersion ()
{
    return JUCE_APPLICATION_VERSION_STRING;
}

void Application::initialise (const juce::String & commandLineArguments)
{
    juce::ignoreUnused (commandLineArguments);
    juce::LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    window = std::make_unique<Window> (JUCE_APPLICATION_NAME_STRING);
}

void Application::shutdown ()
{
    window.reset ();
}

void Application::systemRequestedQuit ()
{
    quit ();
}

bool Application::moreThanOneInstanceAllowed ()
{
    return true;
}

class Application::Window final : public juce::DocumentWindow
{
public:
    explicit Window (const juce::String & name)
        : juce::DocumentWindow {name, juce::Colours::black, TitleBarButtons::allButtons}
    {
        setUsingNativeTitleBar (true);

        static constexpr auto resizable = true;
        static constexpr auto useBottomRightCornerResizer = false;
        setResizable (resizable, useBottomRightCornerResizer);

        static constexpr auto resizeToMatchContent = true;
        setContentOwned (new MainContent, resizeToMatchContent);
        centreWithSize (getWidth (), getHeight ());

        Window::setVisible (true);

        setWantsKeyboardFocus (false);
    }

    void closeButtonPressed () override
    {
        juce::JUCEApplication::getInstance ()->systemRequestedQuit ();
    }
};

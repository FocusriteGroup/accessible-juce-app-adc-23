cmake_minimum_required (VERSION 3.25)

set (APP_NAME "Screen Reader Accessibility Demo")

project (${APP_NAME} VERSION 0.1.0)

include (cpm.cmake)
cpmaddpackage ("gh:juce-framework/juce#7.0.7")

juce_add_gui_app (juce-accessibility-demo PRODUCT_NAME ${APP_NAME})

target_sources (
  juce-accessibility-demo
  PRIVATE src/main.cpp
          src/Application.cpp
          src/Application.h
          src/Button.cpp
          src/Button.h
          src/LookAndFeel.cpp
          src/LookAndFeel.h
          src/MainContent.cpp
          src/MainContent.h
          src/channel-strip/ChannelStrip.cpp
          src/channel-strip/ChannelStrip.h
          src/channel-strip/ChannelStripGroup.cpp
          src/channel-strip/ChannelStripGroup.h
          src/utilities/ExplicitFocusOrder.h)

target_compile_definitions (
  juce-accessibility-demo
  PRIVATE
    DONT_SET_USING_JUCE_NAMESPACE=1
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:juce-accessibility-demo,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:juce-accessibility-demo,JUCE_VERSION>"
)

target_include_directories (juce-accessibility-demo PRIVATE src)

target_link_libraries (
  juce-accessibility-demo PRIVATE juce::juce_gui_basics
  PUBLIC juce::juce_recommended_config_flags juce::juce_recommended_lto_flags
         juce::juce_recommended_warning_flags)

set_target_properties (juce-accessibility-demo PROPERTIES CXX_STANDARD 20)

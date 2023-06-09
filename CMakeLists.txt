cmake_minimum_required(VERSION 3.11)

set(PROJECT "juce-opengl-minimal")
project(${PROJECT} VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(JUCE CONFIG REQUIRED)

juce_add_plugin("juce-opengl-minimal"
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "drlight"                     # Specify the name of the plugin's author
    IS_SYNTH FALSE                              # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE            # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD FALSE               # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE A3AU               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE A3MC                            # A unique four-character plugin id with at least one upper-case character
    PLUGIN_NAME "juce-opengl-minimal"
    FORMATS "Standalone;VST3"                   # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "juce-opengl-minimal"                 # The name of the final executable, which can differ from the target name
)

juce_generate_juce_header("juce-opengl-minimal")

target_sources("juce-opengl-minimal" PRIVATE
    src/AudioProcessor.cc
    src/AudioProcessor.hh
    src/Editor.cc
    src/Editor.hh
    src/StandaloneApp.cc
    src/StandaloneApp.hh
    src/MainWindow.cc
    src/MainWindow.hh
    src/MainComponent.cc
    src/MainComponent.hh
    src/GLComponent.cc
    src/GLComponent.hh
)

target_compile_definitions("juce-opengl-minimal" PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
    DONT_SET_USING_JUCE_NAMESPACE=1
)

target_link_libraries("juce-opengl-minimal" PUBLIC
    juce::juce_audio_utils
    juce::juce_gui_basics
    juce::juce_opengl
)

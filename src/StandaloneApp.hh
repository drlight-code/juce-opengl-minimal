#pragma once

#include <JuceHeader.h>

#include "StandaloneApp.hh"
#include "MainWindow.hh"

class StandaloneApp : public juce::JUCEApplication
{
public:
  StandaloneApp () {}
  ~StandaloneApp ();

  void initialise (juce::String const &commandLine) override;
  void shutdown () override;

  const juce::String getApplicationName () override;
  const juce::String getApplicationVersion () override;

  void systemRequestedQuit () override;

private:

  std::unique_ptr<MainWindow> _mainWindow;
};

// this generates boilerplate code to launch our app class:
START_JUCE_APPLICATION (StandaloneApp)

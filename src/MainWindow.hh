#pragma once

#include <JuceHeader.h>

#include "MainComponent.hh"

class MainWindow : public juce::ResizableWindow
{
public:
  MainWindow (juce::String const &name);

  void userTriedToCloseWindow () override;

private:
  bool keyPressed (const juce::KeyPress &k) override;

  MainComponent _mainComponent;
};

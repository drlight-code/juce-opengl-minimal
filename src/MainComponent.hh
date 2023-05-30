#pragma once

#include <JuceHeader.h>

#include "GLComponent.hh"

class MainComponent : public juce::Component
{
public:
  MainComponent ();

  void paint (juce::Graphics &g) override;
  void resized () override;

private:

  juce::Slider _slider;
  GLComponent _glComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent);
};

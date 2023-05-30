#pragma once

#include <JuceHeader.h>

#include "AudioProcessor.hh"
#include "MainComponent.hh"

class TestEditor : public juce::AudioProcessorEditor
{
public:
  TestEditor (TestAudioProcessor &);
  ~TestEditor ();

  void paint (juce::Graphics &g) override;
  void resized () override;

private:
  MainComponent _mainComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestEditor);
};

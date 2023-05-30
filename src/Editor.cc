#include "Editor.hh"

TestEditor::TestEditor (TestAudioProcessor &p)
    : AudioProcessorEditor (&p), _mainComponent ()
{
}

TestEditor::~TestEditor () {}

void
TestEditor::paint (juce::Graphics &g)
{
  g.fillAll (getLookAndFeel ().findColour (
      juce::ResizableWindow::backgroundColourId));
}

void
TestEditor::resized ()
{
}

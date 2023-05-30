#include "Editor.hh"

TestEditor::TestEditor (TestAudioProcessor &p)
    : AudioProcessorEditor (&p), _mainComponent ()
{
  addChildComponent(_mainComponent);
  _mainComponent.setVisible(true);
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
  _mainComponent.setBounds(getLocalBounds());
}

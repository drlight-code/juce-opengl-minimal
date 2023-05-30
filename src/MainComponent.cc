#include "MainComponent.hh"

MainComponent::MainComponent ()
  : _slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox)
{
  addChildComponent(_slider);
  _slider.setVisible(true);

  addChildComponent(_glComponent);
  _glComponent.setVisible (true);
}

void
MainComponent::paint (juce::Graphics &g)
{
  juce::ignoreUnused (g);
}

void
MainComponent::resized ()
{
  juce::Component::resized ();

  auto const sliderSize = 50;
  _slider.setBounds(0, 0, sliderSize, sliderSize);
  _glComponent.setBounds(getLocalBounds ().withTrimmedTop(sliderSize));
}

#pragma once

#include <JuceHeader.h>

class GLComponent : public juce::Component, public juce::OpenGLRenderer
{
public:
  GLComponent ();
  ~GLComponent ();

  void resized () override;
  void paint (juce::Graphics &g) override;

  void newOpenGLContextCreated () override;
  void renderOpenGL () override;
  void openGLContextClosing () override;

private:
  juce::OpenGLContext _glContext;
};

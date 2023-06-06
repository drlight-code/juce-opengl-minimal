#pragma once

#include <JuceHeader.h>

class GLComponent : public juce::Component, public juce::OpenGLRenderer
{
public:
  GLComponent ();
  ~GLComponent ();

  void resized () override;
  // void paint (juce::Graphics &g) override;

  void newOpenGLContextCreated () override;
  void renderOpenGL () override;
  void openGLContextClosing () override;

private:
  void updateBounds();
  void renderBoundsChanged();
  void drawBlobs(juce::Graphics &g);

      juce::OpenGLContext _glContext;
  std::unique_ptr<juce::Image> _imageBlend;

  // component bounds updated by the UI thread
  juce::Rectangle<int> _bounds;

  // copy of the component bounds for asynchronous use in the GL
  // renderer thread
  std::mutex _mutexBounds;
  juce::Rectangle<int> _boundsRender;
};

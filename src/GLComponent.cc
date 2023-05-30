#include "GLComponent.hh"

GLComponent::GLComponent ()
{
  _glContext.setRenderer (this);
  _glContext.setContinuousRepainting (true);
  _glContext.attachTo (*this);
}

GLComponent::~GLComponent ()
{
  _glContext.detach ();
}

void
GLComponent::paint (juce::Graphics &g)
{
  g.fillAll (juce::Colours::aquamarine);
}

void
GLComponent::resized ()
{
}

void
GLComponent::newOpenGLContextCreated ()
{
  using namespace juce::gl;
  glDebugMessageControl (GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER,
                         GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
}

void
GLComponent::renderOpenGL ()
{
  static auto lastT = std::chrono::high_resolution_clock::now ();

  auto now = std::chrono::high_resolution_clock::now ();
  auto deltaT
      = std::chrono::duration_cast<std::chrono::microseconds> (now - lastT)
            .count ();
  lastT = now;

  juce::Logger::writeToLog ("frametime: " + juce::String (deltaT/1000.f));
}

void
GLComponent::openGLContextClosing ()
{
}

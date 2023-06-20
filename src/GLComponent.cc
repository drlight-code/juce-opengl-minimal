#include "GLComponent.hh"


class GLContextGraphics {
public:
  GLContextGraphics(juce::OpenGLContext &glContext, int width, int height)
      : _glRenderer(
            juce::createOpenGLGraphicsContext(glContext, width, height)),
        _graphics(*_glRenderer) {
    _graphics.addTransform(
        juce::AffineTransform::scale(float(glContext.getRenderingScale())));
  }

  ~GLContextGraphics() { _glRenderer = nullptr; }

  juce::Graphics &get() { return _graphics; }

private:
  std::unique_ptr<juce::LowLevelGraphicsContext> _glRenderer;
  juce::Graphics _graphics;
};

GLComponent::GLComponent ()
{
  _glContext.setRenderer (this);
  _glContext.setComponentPaintingEnabled(false);
  _glContext.setContinuousRepainting (true);
  _glContext.attachTo (*this);
}

GLComponent::~GLComponent ()
{
  _glContext.detach ();
}

// void
// GLComponent::paint (juce::Graphics &g)
// {
// }

void
GLComponent::resized ()
{
  auto lock = std::lock_guard<std::mutex>(_mutexBounds);
  _bounds = getLocalBounds();
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
  using namespace juce::gl;
  using juce::OpenGLHelpers;

  jassert(OpenGLHelpers::isContextActive());

  updateBounds();

  GLContextGraphics graphics(_glContext, //
                             _boundsRender.getWidth(),
                             _boundsRender.getHeight());

  OpenGLHelpers::clear(juce::Colours::black);

  enum class DrawMode {
    OnScreen,
    IntoImage,
    IntoImageLowLevelContext,
    IntoImageAfterGraphicsDestructor
  };

  auto constexpr drawMode = DrawMode::IntoImageAfterGraphicsDestructor;

  switch(drawMode) {
  case DrawMode::OnScreen: {
    // we draw directly using the graphics object that has the OpenGL
    // context attached
    drawBlobs(graphics.get());

    // RESULT: working
    break;
  }

  case DrawMode::IntoImage: {
    // first we need to enable the FBO that is attached to the image
    auto fbo = juce::OpenGLImageType::getFrameBufferFrom(*_imageBlend);
    fbo->makeCurrentAndClear();

    // we draw using a Graphics object that has an Image with
    // OpenGLImageType attached (see renderBoundsChanged())
    juce::Graphics gFBO{*_imageBlend};
    drawBlobs(gFBO);

    // release FBO
    fbo->releaseAsRenderingTarget();

    // afterwards we draw the image using the OpenGL context Graphics
    // object.
    graphics.get().drawImage(*_imageBlend, _boundsRender.toFloat());

    // RESULT:
    // working when useLayer = true (see drawBlobs())
    // incomplete output when useLayer = false (see drawBlobs())
    break;
  }

  case DrawMode::IntoImageLowLevelContext: {
        // first we need to enable the FBO that is attached to the image
        auto fbo = juce::OpenGLImageType::getFrameBufferFrom(*_imageBlend);
        fbo->makeCurrentAndClear();

        // this time create a LowLevelGraphicsContext from the image
        // to initialize our Graphics object
        auto contextFBO = _imageBlend->createLowLevelContext();
        juce::Graphics gFBO {*contextFBO};

        drawBlobs(gFBO);

        // release FBO
        fbo->releaseAsRenderingTarget();

        graphics.get().drawImage(*_imageBlend, _boundsRender.toFloat());

        // RESULT: same as above:
        // working when useLayer = true (see drawBlobs())
        // incomplete output when useLayer = false (see drawBlobs())

        break;
      }

  case DrawMode::IntoImageAfterGraphicsDestructor: {

    // We introduce a local scope to make sure that the Graphics
    // object has been destroyed before we render the Image.
    {
      auto fbo = juce::OpenGLImageType::getFrameBufferFrom(*_imageBlend);
      fbo->makeCurrentAndClear();

      juce::Graphics gFBO{*_imageBlend};
      drawBlobs(gFBO);

      fbo->releaseAsRenderingTarget();
    }

    graphics.get().drawImage(*_imageBlend, _boundsRender.toFloat());

    // RESULT:
    // OpenGL DBG message: GL_INVALID_OPERATION error generated. Target buffer must be bound and not overlapped with mapping range.
    // JUCE Assertion failure in juce_OpenGLContext.cpp:654

    break;
  }
  } // end switch
}

void
GLComponent::drawBlobs(juce::Graphics & g)
{
  using namespace juce::gl;

  auto constexpr blobSize = 500.f;

  auto constexpr drawRect = false;
  auto constexpr useLayer = false;

  if (useLayer)
    g.beginTransparencyLayer(1.f);

  auto area = juce::Rectangle<float>(100.f, 100.f, blobSize, blobSize);
  g.setColour(juce::Colours::red);
  drawRect ? g.fillRect(area) : g.fillEllipse(area);

  area.translate(blobSize / 2.f, 0);
  g.setColour(juce::Colours::blue);
  drawRect ? g.fillRect(area) : g.fillEllipse(area);

  area.translate(blobSize / 2.f, 0);
  g.setColour(juce::Colours::green);
  drawRect ? g.fillRect(area) : g.fillEllipse(area);

  area.translate(blobSize / 2.f, 0);
  g.setColour(juce::Colours::white);
  drawRect ? g.fillRect(area) : g.fillEllipse(area);

  if (useLayer)
    g.endTransparencyLayer();
}

void
GLComponent::updateBounds()
{
  auto lock = std::lock_guard<std::mutex>(_mutexBounds);
  if (_bounds != _boundsRender) {
    _boundsRender = _bounds;
    renderBoundsChanged();
  }
}

void
GLComponent::renderBoundsChanged() {
  juce::Logger::writeToLog(juce::String("bounds changed: ") +
                           juce::String(_boundsRender.getWidth()) + " x " +
                           juce::String(_boundsRender.getHeight()));

  _imageBlend = std::make_unique<juce::Image>(juce::Image::PixelFormat::ARGB, //
                                              _boundsRender.getWidth(),
                                              _boundsRender.getHeight(), //
                                              false, juce::OpenGLImageType());
}

void
GLComponent::openGLContextClosing ()
{
}

#include "StandaloneApp.hh"

StandaloneApp::~StandaloneApp () {}

void
StandaloneApp::initialise (juce::String const &commandLine)
{
  juce::ignoreUnused (commandLine);

  _mainWindow = std::make_unique<MainWindow> (getApplicationName ());
  _mainWindow->setBounds (0, 0, 640, 480);
  _mainWindow->setVisible (true);
}

void
StandaloneApp::shutdown ()
{
  _mainWindow = nullptr;
}

juce::String const
StandaloneApp::getApplicationName ()
{
  return "juce-opengl-minimal";
}

juce::String const
StandaloneApp::getApplicationVersion ()
{
  return "0.0.0";
}

void
StandaloneApp::systemRequestedQuit ()
{
}

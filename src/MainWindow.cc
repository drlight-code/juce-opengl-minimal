#include "MainWindow.hh"

MainWindow::MainWindow (juce::String const &name)
    : juce::ResizableWindow (name, true), _mainComponent ()
{
  setWantsKeyboardFocus (true);

  addChildComponent(_mainComponent);
  _mainComponent.setVisible (true);
}

bool
MainWindow::keyPressed (const juce::KeyPress &k)
{
  if (k.getKeyCode () == juce::KeyPress::escapeKey)
    {
      juce::JUCEApplicationBase::quit ();
      return true;
    }

  return false;
}

void
MainWindow::userTriedToCloseWindow ()
{
  juce::JUCEApplicationBase::quit ();
}

void
MainWindow::resized ()
{
  juce::ResizableWindow::resized ();
  _mainComponent.setBounds(getLocalBounds());
}

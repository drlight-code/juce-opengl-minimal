#include "MainWindow.hh"

MainWindow::MainWindow (juce::String const &name)
    : juce::ResizableWindow (name, true), _mainComponent ()
{
  setWantsKeyboardFocus (true);
  setContentNonOwned(&_mainComponent, false);
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

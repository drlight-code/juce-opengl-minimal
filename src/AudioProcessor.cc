#include "AudioProcessor.hh"
#include "Editor.hh"

TestAudioProcessor::TestAudioProcessor ()
    : AudioProcessor (BusesProperties ().withInput (
        "Input", juce::AudioChannelSet::stereo ()))
{
}

const juce::String
TestAudioProcessor::getName () const
{
  return "juce-opengl-minimal";
}

bool
TestAudioProcessor::acceptsMidi () const
{
  return true;
}

bool
TestAudioProcessor::producesMidi () const
{
  return true;
}

bool
TestAudioProcessor::isMidiEffect () const
{
  return true;
}

double
TestAudioProcessor::getTailLengthSeconds () const
{
  return 0.0;
}

int
TestAudioProcessor::getNumPrograms ()
{
  return 1; // NB: some hosts don't cope very well if you tell
            // them there are 0 programs, so this should be at
            // least 1, even if you're not really implementing
            // programs.
}

int
TestAudioProcessor::getCurrentProgram ()
{
  return 0;
}

void
TestAudioProcessor::setCurrentProgram (int index)
{
  juce::ignoreUnused (index);
}

const juce::String
TestAudioProcessor::getProgramName (int index)
{
  juce::ignoreUnused (index);
  return {};
}

void
TestAudioProcessor::changeProgramName (int index,
                                           const juce::String &newName)
{
  juce::ignoreUnused (index);
  juce::ignoreUnused (newName);
}

void
TestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  juce::ignoreUnused (sampleRate);
  juce::ignoreUnused (samplesPerBlock);
}

void
TestAudioProcessor::releaseResources ()
{
}

bool
TestAudioProcessor::isBusesLayoutSupported (
    const BusesLayout &layouts) const
{
  juce::ignoreUnused (layouts);
  return true;
}

void
TestAudioProcessor::processBlock (juce::AudioBuffer<float> &buffer,
                                      juce::MidiBuffer &midiMessages)
{
  juce::ignoreUnused (buffer);
  juce::ignoreUnused(midiMessages);
}

bool
TestAudioProcessor::hasEditor () const
{
  return true;
}

juce::AudioProcessorEditor *
TestAudioProcessor::createEditor ()
{
  return new TestEditor (*this);
}

void
TestAudioProcessor::getStateInformation (juce::MemoryBlock &destData)
{
  juce::ignoreUnused (destData);
}

void
TestAudioProcessor::setStateInformation (const void *data, int sizeInBytes)
{
  juce::ignoreUnused (data);
  juce::ignoreUnused (sizeInBytes);
}

juce::AudioProcessor *JUCE_CALLTYPE
createPluginFilter ()
{
  return new TestAudioProcessor ();
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>


//==============================================================================
SimpleGainAudioProcessor::SimpleGainAudioProcessor()
{
    gain = DEAFAULT_GAIN_MULTIPLER;
    bypass = false;
}

SimpleGainAudioProcessor::~SimpleGainAudioProcessor()
{
}

//==============================================================================
const String SimpleGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int SimpleGainAudioProcessor::getNumParameters()
{
    // Return total number of parameters
    return totalNumParams;
}

float SimpleGainAudioProcessor::getParameter (int index)
{
    switch (index) {
        case gainParam:
            return gain;
            
        case bypassParam:
            return bypass;
            
        default:
            return 0.0f;
    }
}

void SimpleGainAudioProcessor::setParameter (int index, float newValue)
{
    // newValue always between 0.0f and 1.0f
    switch (index) {
        case gainParam:
            // Map 0.-1. to .1-10.  (10. = 20db, .1 = -20db)
            gain = .1f * expf( GAIN_EXP_CONST * newValue);
            break;
        
        case bypassParam:
            if (newValue > 0.f) {
                bypass = true;
            } else {
                bypass = false;
            }
            break;
            
        default:
            break;
    }
}

const String SimpleGainAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case gainParam:
            return "Gain";
            
        case bypassParam:
            return "Bypass";
            
        default:
            return String::empty;
    }
}

const String SimpleGainAudioProcessor::getParameterText (int index)
{
    return String(getParameter(index), 2);
}

const String SimpleGainAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SimpleGainAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SimpleGainAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool SimpleGainAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool SimpleGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleGainAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double SimpleGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleGainAudioProcessor::getNumPrograms()
{
    return 0;
}

int SimpleGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleGainAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleGainAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void SimpleGainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimpleGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void SimpleGainAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    if (!bypass) {
        
        for (int channel = 0; channel < getNumInputChannels(); ++channel) {
            buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
        }
        
        // In case we have more outputs than inputs, we'll clear any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        {
            buffer.clear (i, 0, buffer.getNumSamples());
        }
        
    }


}

//==============================================================================
bool SimpleGainAudioProcessor::hasEditor() const
{
    // Temporarily false until work on GUI begins
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleGainAudioProcessor::createEditor()
{
    return new SimpleGainAudioProcessorEditor (this);
}

//==============================================================================
void SimpleGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleGainAudioProcessor();
}

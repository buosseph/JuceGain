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
JuceGainAudioProcessor::JuceGainAudioProcessor()
{
    gain = DEFAULT_GAIN;
    gain_db = .1f * expf( GAIN_EXP_CONST * DEFAULT_GAIN);
    pan = DEFAULT_PAN_CENTER;
    bypass = false;
}

JuceGainAudioProcessor::~JuceGainAudioProcessor()
{
}

//==============================================================================
const String JuceGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JuceGainAudioProcessor::getNumParameters()
{
    // Return total number of parameters
    return totalNumParams;
}

float JuceGainAudioProcessor::getParameter (int index)
{
    switch (index) {
        case gainParam:
            return gain;
            
        case panParam:
            return pan;
            
        case bypassParam:
            return bypass;
            
        default:
            return 0.0f;
    }
}

void JuceGainAudioProcessor::setParameter (int index, float newValue)
{
    // newValue always between 0.0f and 1.0f
    switch (index) {
        case gainParam:
            gain = newValue;
            // Map 0.-1. to .1-10.  (10. = 20db, .1 = -20db)
            gain_db = .1f * expf( GAIN_EXP_CONST * newValue);
            break;
        
        case panParam:
            // 0 = L, 0.5 = C, 1 = R
            pan = newValue;
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

const String JuceGainAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case gainParam:
            return "Gain";
            
        case panParam:
            return "Pan";
            
        case bypassParam:
            return "Bypass";
            
        default:
            return String::empty;
    }
}

const String JuceGainAudioProcessor::getParameterText (int index)
{
    return String(getParameter(index), 2);
}

const String JuceGainAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JuceGainAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JuceGainAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool JuceGainAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool JuceGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceGainAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JuceGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceGainAudioProcessor::getNumPrograms()
{
    return 0;
}

int JuceGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceGainAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceGainAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void JuceGainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceGainAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    if (!bypass) {
        
        float* leftChannel = buffer.getWritePointer(0);
        float* rightChannel = buffer.getWritePointer(1);
        
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            /* Linear Pan Law (-6db center, not constant):
                leftChannel[i] = leftChannel[i] * (1.f - pan);
                rightChannel[i] = rightChannel[i] * pan;
             */

            /* Constant Power Pan Law (-3db center, thus THREE_DB used to raise center):
                leftChannel[i] = leftChannel[i] * cosf(pan * M_PI_2) * THREE_DB;
                rightChannel[i] = rightChannel[i] * sinf(pan * M_PI_2) * THREE_DB;
             */
            
            
            leftChannel[i] = leftChannel[i] * gain_db * cosf(pan * M_PI_2) * THREE_DB;
            rightChannel[i] = rightChannel[i] * gain_db * sinf(pan * M_PI_2) * THREE_DB;
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
bool JuceGainAudioProcessor::hasEditor() const
{
    // Temporarily false until work on GUI begins
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceGainAudioProcessor::createEditor()
{
    return new JuceGainAudioProcessorEditor (*this);
}


//==============================================================================
void JuceGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceGainAudioProcessor();
}
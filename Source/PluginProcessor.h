/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class JuceGainAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceGainAudioProcessor();
    ~JuceGainAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);
    float getParameterDefaultValue(int index);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    // Parameter indices
    enum Parameters
    {
        gainParam,
        panParam,
//        bypassParam,
        totalNumParams
    };
    
    // User parameters
    float uGain, uGainDb, uPan;
    
private:
    //==============================================================================
    
    // Default values
    const float GAIN_EXP_CONST = logf(10.f/.1f);
    const float DEFAULT_GAIN    = .5f;
    const float THREE_DB        = 1.41254f;
    const float DEFAULT_PAN     = .5f;

    // Algorithm parameters
    float aGain, aGainDb, aPan;
//    bool bypass;

    // In-loop values
    float leftPanGain, rightPanGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceGainAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
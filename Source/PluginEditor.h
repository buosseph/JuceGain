/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_2D04B386A627E93D__
#define __JUCE_HEADER_2D04B386A627E93D__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginLookAndFeel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JuceGainAudioProcessorEditor  : public AudioProcessorEditor,
                                      public Timer,
                                      public SliderListener
{
public:
    //==============================================================================
    JuceGainAudioProcessorEditor (JuceGainAudioProcessor& p);
    ~JuceGainAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceGainAudioProcessor& processor;

    JuceGainAudioProcessor& getProcessor() const
    {
        return static_cast<JuceGainAudioProcessor&> (processor);
    }

    PluginLookAndFeel pluginLookAndFeel;
    
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> gainDbSlider;
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<Label> panLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceGainAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2D04B386A627E93D__

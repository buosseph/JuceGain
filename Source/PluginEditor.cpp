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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JuceGainAudioProcessorEditor::JuceGainAudioProcessorEditor (JuceGainAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (gainDbSlider = new Slider ("Gain Slider"));
    gainDbSlider->setTooltip (TRANS("Adjusts output volume"));
    gainDbSlider->setRange (-96, 10, 0.01);
    gainDbSlider->setSliderStyle (Slider::LinearVertical);
    gainDbSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    gainDbSlider->setColour (Slider::thumbColourId, Colours::grey);
    gainDbSlider->addListener (this);

    addAndMakeVisible (panSlider = new Slider ("Pan Rotary"));
    panSlider->setTooltip (TRANS("Adjusts signal balance"));
    panSlider->setRange (-50, 50, 1);
    panSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    panSlider->setColour (Slider::rotarySliderFillColourId, Colours::grey);
    panSlider->addListener (this);


    //[UserPreSize]
    gainDbSlider->setTextValueSuffix("db");

    gainDbSlider->setDoubleClickReturnValue(true, 0);
    panSlider->setDoubleClickReturnValue(true, 0);
    //[/UserPreSize]

    setSize (240, 320);


    //[Constructor] You can add your own custom stuff here..
    startTimer(50);
    //[/Constructor]
}

JuceGainAudioProcessorEditor::~JuceGainAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainDbSlider = nullptr;
    panSlider = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    deleteAllChildren();
    //[/Destructor]
}

//==============================================================================
void JuceGainAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff222222));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceGainAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gainDbSlider->setBounds (24, 24, 60, 260);
    panSlider->setBounds (152, 192, 60, 90);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JuceGainAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainDbSlider)
    {
        //[UserSliderCode_gainDbSlider] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            JuceGainAudioProcessor::Parameters::gainParam,
            (float) (sliderThatWasMoved->getValue() + 96.f) / 106.f // map to 0.-1.f (uGain)
        );
        //[/UserSliderCode_gainDbSlider]
    }
    else if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            JuceGainAudioProcessor::Parameters::panParam,
            (float) (sliderThatWasMoved->getValue() + 50.f) / 100.f // map to 0.-1.f
        );
        //[/UserSliderCode_panSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void JuceGainAudioProcessorEditor::timerCallback() {
    // Timer conflicts cause UI stuttering, this is due to the values not being mapped back
    JuceGainAudioProcessor& ourProcessor = getProcessor();

    gainDbSlider->setValue(
        (106.f * ourProcessor.uGain - 96.f),
        dontSendNotification
    );
    
    panSlider->setValue(
        (100.f * ourProcessor.uPan - 50.f),
        dontSendNotification
    );
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JuceGainAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="JuceGainAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor (&amp;p), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="240" initialHeight="320">
  <BACKGROUND backgroundColour="ff222222"/>
  <SLIDER name="Gain Slider" id="869ad7b78e733129" memberName="gainDbSlider"
          virtualName="" explicitFocusOrder="0" pos="24 24 60 260" tooltip="Adjusts output volume"
          thumbcol="ff808080" min="-96" max="10" int="0.010000000000000000208"
          style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pan Rotary" id="7de69cf8fd092825" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="152 192 60 90" tooltip="Adjusts signal panning"
          rotarysliderfill="ff808080" min="-50" max="50" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

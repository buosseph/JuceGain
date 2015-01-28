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
//    gainDbSlider->setRange (0, 1, 0.01);
    gainDbSlider->setRange (-96, 10);     // 0db = 1.f  Causes GUI issues
    gainDbSlider->setSliderStyle (Slider::LinearVertical);
    gainDbSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    gainDbSlider->setColour (Slider::thumbColourId, Colours::grey);
    gainDbSlider->addListener (this);

    addAndMakeVisible (panSlider = new Slider ("Pan Knob"));
    panSlider->setRange (0, 1, 0.005);             // L = 0.f, R = 1.f
//    panSlider->setRange (-50, 50);       // L = -50, R = 50   Causes GUI issues
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    panSlider->setColour (Slider::rotarySliderFillColourId, Colours::grey);
    panSlider->addListener (this);

    addAndMakeVisible (gainDbLabel = new Label ("Gain Label",
                                                TRANS("db")));
    gainDbLabel->setFont (Font (15.00f, Font::plain));
    gainDbLabel->setJustificationType (Justification::centredLeft);
    gainDbLabel->setEditable (false, false, false);
    gainDbLabel->setColour (Label::textColourId, Colours::white);
    gainDbLabel->setColour (TextEditor::textColourId, Colours::black);
    gainDbLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (240, 320);
    startTimer(50);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

JuceGainAudioProcessorEditor::~JuceGainAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainDbSlider = nullptr;
    panSlider = nullptr;
    gainDbLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
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
    gainDbLabel->setBounds (88, 266, 32, 16);
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
            (float) sliderThatWasMoved->getValue()
        );
        //[/UserSliderCode_gainDbSlider]
    }
    else if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            JuceGainAudioProcessor::Parameters::panParam,
            (float) sliderThatWasMoved->getValue()
        );
        //[/UserSliderCode_panSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void JuceGainAudioProcessorEditor::timerCallback() {
    JuceGainAudioProcessor& ourProcessor = getProcessor();

    gainDbSlider->setValue(
        ourProcessor.uGainDb,
        dontSendNotification
    );
    panSlider->setValue(
        ourProcessor.uPan,
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
                 constructorParams="JuceGainAudioProcessor* processor" variableInitialisers="JuceGainAudioProcessorEditor(processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="240" initialHeight="320">
  <BACKGROUND backgroundColour="ff222222"/>
  <SLIDER name="Gain Slider" id="869ad7b78e733129" memberName="gainDbSlider"
          virtualName="" explicitFocusOrder="0" pos="24 24 60 260" thumbcol="ff808080"
          min="0" max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pan Rotary" id="7b6904ab8ead2ca2" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="152 192 60 90" rotarysliderfill="ff808080"
          min="0" max="1" int="0.010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Gain Label" id="da142ff8b5140aee" memberName="gainDbLabel"
         virtualName="" explicitFocusOrder="0" pos="88 266 32 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="db" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

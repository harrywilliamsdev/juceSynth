
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
SynthTakeIiAudioProcessorEditor::SynthTakeIiAudioProcessorEditor (SynthTakeIiAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    setSize (800, 400); // Sets the editor size in PIXELS
    
    
    /*
     
     Declare all slider objects, set the properites (style, colour etc).
     Add a label to each slider
     add the slider attachment to pass the slider/dial values into the AudioParameterValueTreeState
     
     */
    
     
// OSCILLATOR 1
    
    
    // TYPE SLIDER
    osc_1_SliderType.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc_1_SliderType.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
    osc_1_SliderType.setColour(Slider::thumbColourId, hw_colour_6);
    osc_1_SliderType.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(osc_1_SliderType); // ADD TO EDITOR COMPONENT
    
    osc1_wave_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC1_WAVE", osc_1_SliderType);
    
    // TYPE LABEL
    osc_1_SliderType_Label.setFont(15.f);
    osc_1_SliderType_Label.setText("Waveform", NotificationType::dontSendNotification);
    osc_1_SliderType_Label.setJustificationType(Justification::centred);
    osc_1_SliderType_Label.attachToComponent(&osc_1_SliderType, false);
    addAndMakeVisible(osc_1_SliderType_Label);
    
    osc_1_SliderPitch.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc_1_SliderPitch.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
    osc_1_SliderPitch.setColour(Slider::thumbColourId, hw_colour_6);
    osc_1_SliderPitch.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    osc_1_SliderPitch.setTextValueSuffix(" st");
    addAndMakeVisible(osc_1_SliderPitch);
    
    osc1_pitch_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC1_PITCH", osc_1_SliderPitch);
    
    osc_1_SliderPitch_Label.setFont(15.f);
    osc_1_SliderPitch_Label.setText("Pitch", NotificationType::dontSendNotification);
    osc_1_SliderPitch_Label.setJustificationType(Justification::centred);
    osc_1_SliderPitch_Label.attachToComponent(&osc_1_SliderPitch, false);
    addAndMakeVisible(osc_1_SliderPitch_Label);
    
osc_1_SliderDetune.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc_1_SliderDetune.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
    osc_1_SliderDetune.setColour(Slider::thumbColourId, hw_colour_6);
    osc_1_SliderDetune.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(osc_1_SliderDetune);
    
    osc1_detune_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC1_DETUNE", osc_1_SliderDetune);
    
    osc_1_SliderDetune_Label.setFont(15.f);
    osc_1_SliderDetune_Label.setText("Detune", NotificationType::dontSendNotification);
    osc_1_SliderDetune_Label.setJustificationType(Justification::centred);
    osc_1_SliderDetune_Label.attachToComponent(&osc_1_SliderDetune, false);
    addAndMakeVisible(osc_1_SliderDetune_Label);
    
// OSCILLATOR 2
    
      osc_2_SliderType.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        osc_2_SliderType.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
        osc_2_SliderType.setColour(Slider::thumbColourId, hw_colour_6);
        osc_2_SliderType.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
        addAndMakeVisible(osc_2_SliderType);
    
    osc2_wave_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC2_WAVE", osc_2_SliderType);
        
        osc_2_SliderType_Label.setFont(15.f);
        osc_2_SliderType_Label.setText("Waveform", NotificationType::dontSendNotification);
        osc_2_SliderType_Label.setJustificationType(Justification::centred);
        osc_2_SliderType_Label.attachToComponent(&osc_2_SliderType, false);
        addAndMakeVisible(osc_2_SliderType_Label);
        
        osc_2_SliderPitch.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        osc_2_SliderPitch.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
        osc_2_SliderPitch.setColour(Slider::thumbColourId, hw_colour_6);
        osc_2_SliderPitch.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    osc_2_SliderPitch.setTextValueSuffix( " st");
        addAndMakeVisible(osc_2_SliderPitch);
    
    osc2_pitch_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC2_PITCH", osc_2_SliderPitch);
        
        osc_2_SliderPitch_Label.setFont(15.f);
        osc_2_SliderPitch_Label.setText("Pitch", NotificationType::dontSendNotification);
        osc_2_SliderPitch_Label.setJustificationType(Justification::centred);
        osc_2_SliderPitch_Label.attachToComponent(&osc_2_SliderPitch, false);
        addAndMakeVisible(osc_1_SliderPitch_Label);
        
    osc_2_SliderDetune.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        osc_2_SliderDetune.setColour(Slider::rotarySliderFillColourId, hw_colour_5);
        osc_2_SliderDetune.setColour(Slider::thumbColourId, hw_colour_6);
        osc_2_SliderDetune.setRange(-50, 50, 0.5);
        osc_2_SliderDetune.setValue(0);
        osc_2_SliderDetune.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
        addAndMakeVisible(osc_2_SliderDetune);
    
    osc2_detune_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC2_DETUNE", osc_2_SliderDetune);
        
        osc_2_SliderDetune_Label.setFont(15.f);
        osc_2_SliderDetune_Label.setText("Detune", NotificationType::dontSendNotification);
        osc_2_SliderDetune_Label.setJustificationType(Justification::centred);
        osc_2_SliderDetune_Label.attachToComponent(&osc_2_SliderDetune, false);
        addAndMakeVisible(osc_2_SliderDetune_Label);
    
// FILTER BANK
        
    
    filter_SliderCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filter_SliderCutoff.setColour(Slider::rotarySliderFillColourId, Colours::limegreen);
    filter_SliderCutoff.setColour(Slider::thumbColourId, Colours::green);
    filter_SliderCutoff.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    filter_SliderCutoff.setTextValueSuffix(" Hz");
    addAndMakeVisible(filter_SliderCutoff);
    
    filter_SliderCutoff_Label.setFont(15.f);
    filter_SliderCutoff_Label.setText("Cutoff", NotificationType::dontSendNotification);
    filter_SliderCutoff_Label.setJustificationType(Justification::centred);
    filter_SliderCutoff_Label.attachToComponent(&filter_SliderCutoff, false);
    addAndMakeVisible(filter_SliderCutoff_Label);
    
    filter_cutoff_sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "FILTER_CUTOFF", filter_SliderCutoff);
    
    
    filter_SliderResonance.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
       filter_SliderResonance.setColour(Slider::rotarySliderFillColourId, Colours::limegreen);
    filter_SliderResonance.setColour(Slider::thumbColourId, Colours::green);
       filter_SliderResonance.setRange(0,1,0.01);
       filter_SliderResonance.setValue(0.2);
       filter_SliderResonance.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
       addAndMakeVisible(filter_SliderResonance);
       
       filter_SliderResonance_Label.setFont(15.f);
       filter_SliderResonance_Label.setText("Resonance", NotificationType::dontSendNotification);
       filter_SliderResonance_Label.setJustificationType(Justification::centred);
       filter_SliderResonance_Label.attachToComponent(&filter_SliderResonance, false);
       addAndMakeVisible(filter_SliderResonance_Label);
    
    filter_resonance_sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "FILTER_RESONANCE", filter_SliderResonance);

    
    
    filter_SliderEG.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
          filter_SliderEG.setColour(Slider::rotarySliderFillColourId, Colours::limegreen);
       filter_SliderEG.setColour(Slider::thumbColourId, Colours::green);
          filter_SliderEG.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
          addAndMakeVisible(filter_SliderEG);
          
          filter_SliderEG_Label.setFont(15.f);
          filter_SliderEG_Label.setText("EG Amount", NotificationType::dontSendNotification);
          filter_SliderEG_Label.setJustificationType(Justification::centred);
          filter_SliderEG_Label.attachToComponent(&filter_SliderEG, false);
          addAndMakeVisible(filter_SliderEG_Label);
    
    filter_eg_amount_slider_Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "FILTER_EG_AMOUNT", filter_SliderEG);
    
// ADSR Sliders
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setColour(Slider::trackColourId, hw_colour_1);
    attackSlider.setColour(Slider::thumbColourId, hw_colour_4);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(attackSlider);
    
    attack_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "ATTACK", attackSlider);
    
    attackLabel.setFont(15.f);
    attackLabel.setText("Attack", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::centred);
    attackLabel.attachToComponent(&attackSlider, false);
    addAndMakeVisible(attackLabel);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setColour(Slider::trackColourId, hw_colour_1);
    decaySlider.setColour(Slider::thumbColourId, hw_colour_4);
    decaySlider.setRange(0.0, 5.0, 1);
    decaySlider.setValue(1.0);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(decaySlider);
    
    decay_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DECAY", decaySlider);
    
    decayLabel.setFont(15.f);
    decayLabel.setText("Decay", NotificationType::dontSendNotification);
    decayLabel.setJustificationType(Justification::centred);
    decayLabel.attachToComponent(&decaySlider, false);
    addAndMakeVisible(decayLabel);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setColour(Slider::trackColourId, hw_colour_1);
    sustainSlider.setColour(Slider::thumbColourId, hw_colour_4);
    sustainSlider.setRange(0.0, 1.0, 0.01);
    sustainSlider.setValue(0.8);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(sustainSlider);
    
    sustain_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "SUSTAIN", sustainSlider);
    
    sustainLabel.setFont(15.f);
    sustainLabel.setText("Sustain", NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(Justification::centred);
    sustainLabel.attachToComponent(&sustainSlider, false);
    addAndMakeVisible(sustainLabel);
    
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setColour(Slider::trackColourId, hw_colour_1);
    releaseSlider.setColour(Slider::thumbColourId, hw_colour_4);
    releaseSlider.setRange(0.0, 5.0, 1);
    releaseSlider.setValue(3.0);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(releaseSlider);
    
    release_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "RELEASE", releaseSlider);
    
    releaseLabel.setFont(15.f);
    releaseLabel.setText("Release", NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(Justification::centred);
    releaseLabel.attachToComponent(&releaseSlider, false);
    addAndMakeVisible(releaseLabel);
    
    // LFO SECTION
    
    lfo_SliderRate.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfo_SliderRate.setColour(Slider::thumbColourId, Colours::cyan);
    lfo_SliderRate.setColour(Slider::rotarySliderFillColourId, Colours::blue);
    lfo_SliderRate.setRange(0.1, 10, 0.01);
    lfo_SliderRate.setValue(3.5);
    lfo_SliderRate.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(lfo_SliderRate);
    
    lfo_rate_sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "RATE", lfo_SliderRate);
    
    lfo_SliderRate_Label.setFont(15.f);
    lfo_SliderRate_Label.setText("LFO Rate", NotificationType::dontSendNotification);
    lfo_SliderRate_Label.setJustificationType(Justification::centred);
    lfo_SliderRate_Label.attachToComponent(&lfo_SliderRate, false);
    addAndMakeVisible(lfo_SliderRate_Label);
    
    lfo_SliderDepth.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfo_SliderDepth.setColour(Slider::thumbColourId, Colours::cyan);
    lfo_SliderDepth.setColour(Slider::rotarySliderFillColourId, Colours::blue);
    lfo_SliderDepth.setRange(0.1, 5, 0.01);
    lfo_SliderDepth.setValue(3.5);
    lfo_SliderDepth.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(lfo_SliderDepth);
    
    lfo_depth_sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DEPTH", lfo_SliderDepth);
    
    lfo_SliderDepth_Label.setFont(15.f);
    lfo_SliderDepth_Label.setText("LFO Depth", NotificationType::dontSendNotification);
    lfo_SliderDepth_Label.setJustificationType(Justification::centred);
    lfo_SliderDepth_Label.attachToComponent(&lfo_SliderDepth, false);
    addAndMakeVisible(lfo_SliderDepth_Label);
    
    
// OUTPUT GAIN
    
    outputGainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputGainSlider.setColour(Slider::thumbColourId, Colours::white);
    outputGainSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightgrey);
    outputGainSlider.setRange(-48, 6, 0.01);
    outputGainSlider.setValue(0.0);
    outputGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(outputGainSlider);
    
    outputGainLabel.setFont(15.f);
          outputGainLabel.setText("O/P Gain", NotificationType::dontSendNotification);
          outputGainLabel.setJustificationType(Justification::centred);
          outputGainLabel.attachToComponent(&outputGainSlider, false);
          addAndMakeVisible(outputGainLabel);
    
    outputGain_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OUTPUT", outputGainSlider);
    
    
    // DISTORTION
    
    distortionSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    distortionSlider.setColour(Slider::thumbColourId, Colours::wheat);
    distortionSlider.setColour(Slider::rotarySliderFillColourId, Colours::firebrick);
    distortionSlider.setRange(0.0, 5.0, 0.01);
    distortionSlider.setValue(0.0);
    distortionSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(distortionSlider);
    
    distortionSlider_Label.setFont(15.f);
    distortionSlider_Label.setText("Saturation", dontSendNotification);
    distortionSlider_Label.setJustificationType(Justification::centred);
    distortionSlider_Label.attachToComponent(&distortionSlider, false);
    addAndMakeVisible(distortionSlider_Label);
    
    distortion_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DISTORTION", distortionSlider);
    
        // DISTORTION BLEND
    
    distortion_WetDry_Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
       distortion_WetDry_Slider.setColour(Slider::thumbColourId, Colours::wheat);
       distortion_WetDry_Slider.setColour(Slider::rotarySliderFillColourId, Colours::firebrick);
       distortion_WetDry_Slider.setRange(0.0, 5.0, 0.01);
       distortion_WetDry_Slider.setValue(0.0);
       distortion_WetDry_Slider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
       addAndMakeVisible(distortion_WetDry_Slider);
       
       distortion_WetDry_Slider_Label.setFont(15.f);
       distortion_WetDry_Slider_Label.setText("Dist W/D", dontSendNotification);
       distortion_WetDry_Slider_Label.setJustificationType(Justification::centred);
       distortion_WetDry_Slider_Label.attachToComponent(&distortion_WetDry_Slider, false);
       addAndMakeVisible(distortion_WetDry_Slider_Label);
       
    distortion_wetdry_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DISTORTION_WETDRY", distortion_WetDry_Slider);
       
    
    // DELAY
    
    delay_TimeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delay_TimeSlider.setColour(Slider::thumbColourId, Colours::purple);
    delay_TimeSlider.setColour(Slider::rotarySliderFillColourId, Colours::rebeccapurple);
    delay_TimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delay_TimeSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(delay_TimeSlider);
    
    delay_time_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DELAY_TIME", delay_TimeSlider);
    
    delay_TimeSlider_Label.setFont(15.f);
    delay_TimeSlider_Label.setText("D Time", dontSendNotification);
    delay_TimeSlider_Label.setJustificationType(Justification::centred);
    delay_TimeSlider_Label.attachToComponent(&delay_TimeSlider, false);
    addAndMakeVisible(delay_TimeSlider_Label);
    
        //FEEDBACK
    
   delay_FeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
      delay_FeedbackSlider.setColour(Slider::thumbColourId, Colours::purple);
      delay_FeedbackSlider.setColour(Slider::rotarySliderFillColourId, Colours::rebeccapurple);
      delay_FeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
      addAndMakeVisible(delay_FeedbackSlider);
      
      delay_feedback_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DELAY_FEEDBACK", delay_FeedbackSlider);
      
      delay_FeedbackSlider_Label.setFont(15.f);
      delay_FeedbackSlider_Label.setText("Repeats", dontSendNotification);
      delay_FeedbackSlider_Label.setJustificationType(Justification::centred);
      delay_FeedbackSlider_Label.attachToComponent(&delay_FeedbackSlider, false);
      addAndMakeVisible(delay_FeedbackSlider_Label);
    
        // Modulation
    
    delay_modulationSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        delay_modulationSlider.setColour(Slider::thumbColourId, Colours::purple);
        delay_modulationSlider.setColour(Slider::rotarySliderFillColourId, Colours::rebeccapurple);
        delay_modulationSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delay_modulationSlider.setTextValueSuffix(" Hz");
        addAndMakeVisible(delay_modulationSlider);
        
        delay_modulation_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DELAY_MODULATION", delay_modulationSlider);
    
    delay_modulationSlider_Label.setFont(15.f);
    delay_modulationSlider_Label.setText("Mod", dontSendNotification);
    delay_modulationSlider_Label.setJustificationType(Justification::centred);
    delay_modulationSlider_Label.attachToComponent(&delay_modulationSlider, false);
    
        // WET DRY BLEND
    delay_WetDrySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
           delay_WetDrySlider.setColour(Slider::thumbColourId, Colours::purple);
           delay_WetDrySlider.setColour(Slider::rotarySliderFillColourId, Colours::rebeccapurple);
           delay_WetDrySlider.setRange(0.0, 2000,0.01);
           delay_WetDrySlider.setValue(75);
    delay_WetDrySlider.setTextBoxStyle(Slider::NoTextBox, true, 50, 20);
           addAndMakeVisible(delay_WetDrySlider);
           
    delay_wetdry_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DELAY_WETDRY", delay_WetDrySlider);
       
    delay_WetDrySlider_Label.setFont(10.f);
    delay_WetDrySlider_Label.setText("Delay W/D", dontSendNotification);
    delay_WetDrySlider_Label.setJustificationType(Justification::centred);
    delay_WetDrySlider_Label.attachToComponent(&delay_WetDrySlider, true);
        // Stereo Groove Slider
    delay_grooveSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delay_grooveSlider.setColour(Slider::thumbColourId, Colours::purple);
    delay_grooveSlider.setColour(Slider::trackColourId, Colours::rebeccapurple);
    delay_grooveSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delay_grooveSlider.setValue(1);
    addAndMakeVisible(delay_grooveSlider);
    
    delay_groove_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DELAY_GROOVE", delay_grooveSlider);
    
    delay_grooveSlider_Label.setFont(15.f);
    delay_grooveSlider_Label.setText("Stereo Groove", dontSendNotification);
    delay_grooveSlider_Label.setJustificationType(Justification::centred);
    delay_grooveSlider_Label.attachToComponent(&delay_grooveSlider, false);
    
    
    
    // PAN POT
    
    panSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    panSlider.setColour(Slider::thumbColourId, Colours::white);
    panSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightgrey);
    panSlider.setRange(-1, 1, 0.01);
    panSlider.setValue(0);
    panSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(panSlider);
    
    panLabel.setFont(15.f);
    panLabel.setText("Pan", dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    panLabel.attachToComponent(&panSlider, false);
    
    pan_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "PAN", panSlider);
    
    
    // Oscillator Attachments
    
    osc1_volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1_volumeSlider.setColour(Slider::trackColourId, Colours::white);
    osc1_volumeSlider.setColour(Slider::thumbColourId, Colours::lightgrey);
    osc1_volumeSlider.setRange(0.0, 5.0, 1);
    osc1_volumeSlider.setValue(2.5);
    osc1_volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(osc1_volumeSlider);
    
    osc1_volume_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC1_VOLUME", osc1_volumeSlider);
    
    osc1_volumeSlider_Label.setFont(15.f);
    osc1_volumeSlider_Label.setText("Osc I", NotificationType::dontSendNotification);
    osc1_volumeSlider_Label.setJustificationType(Justification::centred);
    osc1_volumeSlider_Label.attachToComponent(&osc1_volumeSlider, false);
    addAndMakeVisible(osc1_volumeSlider_Label);
    
    
    
    
    osc2_volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2_volumeSlider.setColour(Slider::trackColourId, Colours::white);
    osc2_volumeSlider.setColour(Slider::thumbColourId, Colours::lightgrey);
    osc2_volumeSlider.setRange(0.0, 5.0, 1);
    osc2_volumeSlider.setValue(2.5);
    osc2_volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(osc2_volumeSlider);
    
    osc2_volume_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSC2_VOLUME", osc2_volumeSlider);
    
    osc2_volumeSlider_Label.setFont(15.f);
    osc2_volumeSlider_Label.setText("Osc II", NotificationType::dontSendNotification);
    osc2_volumeSlider_Label.setJustificationType(Justification::centred);
    osc2_volumeSlider_Label.attachToComponent(&osc2_volumeSlider, false);
    addAndMakeVisible(osc2_volumeSlider_Label);
    
    
    oscNoise_volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    oscNoise_volumeSlider.setColour(Slider::trackColourId, Colours::white);
    oscNoise_volumeSlider.setColour(Slider::thumbColourId, Colours::lightgrey);
    oscNoise_volumeSlider.setRange(0.0, 5.0, 1);
    oscNoise_volumeSlider.setValue(2.5);
    oscNoise_volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(oscNoise_volumeSlider);
    
    oscNoise_volume_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OSCNOISE_VOLUME", oscNoise_volumeSlider);
    
    oscNoise_volumeSlider_Label.setFont(15.f);
    oscNoise_volumeSlider_Label.setText("Noise", NotificationType::dontSendNotification);
    oscNoise_volumeSlider_Label.setJustificationType(Justification::centred);
    oscNoise_volumeSlider_Label.attachToComponent(&oscNoise_volumeSlider, false);
    addAndMakeVisible(oscNoise_volumeSlider_Label);
    
    // Noise Colour
    
    oscNoise_colour_Slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    oscNoise_colour_Slider.setColour(Slider::thumbColourId, Colours::limegreen);
    oscNoise_colour_Slider.setColour(Slider::trackColourId, Colours::green);
    oscNoise_colour_Slider.setTextBoxStyle(Slider::NoTextBox, true, 50, 20);
    addAndMakeVisible(oscNoise_colour_Slider);
    
    osc_noise_volume_sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "NOISE_COLOUR", oscNoise_colour_Slider);
    
    oscNoise_colour_Slider_Label.setFont(12.5f);
    oscNoise_colour_Slider_Label.setText("Noise Colour", NotificationType::dontSendNotification);
    oscNoise_colour_Slider_Label.setJustificationType(Justification::centred);
    oscNoise_colour_Slider_Label.attachToComponent(&oscNoise_colour_Slider, false);
    addAndMakeVisible(oscNoise_colour_Slider_Label);
    
    // FILTER COMBOX
    
    filter_type_comboBox.addItem("LPF", 1);
    filter_type_comboBox.addItem("HPF", 2);
    addAndMakeVisible(filter_type_comboBox);
    
    filter_type_ComboBox_Attachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.apvts,"FILTER_TYPE", filter_type_comboBox);
    
    // COMBOX FOR LFO WAVE
    
    waveformComboBox.addItem("sin", 1);
    waveformComboBox.addItem("tri", 2);
    waveformComboBox.addItem("sqr", 3);
    waveformComboBox.setText("wave");
    addAndMakeVisible(waveformComboBox);
    
    lfo_waveform_comboBox_attachment = make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.apvts, "LFO_WAVE", waveformComboBox);
    
    // COMBOBOX FOR DIST TYPE
    
    distortion_ComboBox.addItem("Hyp Tan", 1);
    distortion_ComboBox.addItem("Arc Tan",2 );
    distortion_ComboBox.addItem("Sigmoid", 3);
    distortion_ComboBox.addItem("Fuzz", 4);
    addAndMakeVisible(distortion_ComboBox);
    
    distortion_ComboBox_Attachment = make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.apvts, "DISTORTION_TYPE", distortion_ComboBox);
    
    distortionType_Label.setFont(15.f);
    distortionType_Label.setText("Dist Type", dontSendNotification);
    distortionType_Label.setJustificationType(Justification::centred);
    distortionType_Label.attachToComponent(&distortion_ComboBox, false);
    
}

SynthTakeIiAudioProcessorEditor::~SynthTakeIiAudioProcessorEditor()
{
}

//==============================================================================
void SynthTakeIiAudioProcessorEditor::paint (Graphics& g)
{
    // Set background colour overall
    g.fillAll (Colours::black);
    
    // SECTION FRAME/BORDERS
    g.setColour(Colours::gold);
    g.drawRect(0, 0, 100, 400);
    g.drawRect(100, 0, 100, 400);
    g.drawRect(200, 0, 100, 400);
    g.drawRect(300, 0, 225, 240);
    g.drawRect(300, 240, 225, 160);
    g.drawRect(525, 0, 275, 240);
    g.drawRect(525, 240, 275, 160);
    

    // OSC FILL
    g.setColour(Colours::orangered);
    g.setOpacity(0.15);
    g.fillRect(0, 0, 100, 400);
    g.fillRect(100, 0, 100, 400);
    // FILTER FILL
    g.setColour(Colours::lightgreen);
    g.setOpacity(0.15);
    g.fillRect(200, 0, 100, 400);
    // LFO FILL
    g.setColour(Colours::blue);
    g.setOpacity(0.15);
    g.fillRect(300, 240, 225, 160);
    // ENV FILL
    g.setColour(Colours::purple);
    g.setOpacity(0.15);
    g.fillRect(300, 0, 225, 240);
    // FX FILLS
    g.setColour(Colours::brown);
    g.setOpacity(0.1);
    g.fillRect(525, 0,275,120);
    g.setColour(Colours::whitesmoke);
    g.setOpacity(0.1);
    g.fillRect(525,120,275,120);
        
}

void SynthTakeIiAudioProcessorEditor::resized()
{
    
    /*
            LAYOUT SECTION
        TO DO:
        GET RID OF MAGIC NUMBERS - SET A FEW DIFFERENT SIZE VARIABLES
     
        SLIDER HEIGHT
        SLIDER WIDTH
        KNOB HEIGHT
        KNOB WIDTH
     
        Then use the master height and width to dynamically arrange your components
     */
    
    // SLIDER DIMENSION DECLARTIONS
    
    // VERTICAL SLIDER
   const int sliderWidth = 75;
   const int sliderHeight = 200;
    // GENERAL KNOB
   const int knobWidth = 80;
   const int knobHeight = 100;
    // LARGE KNOB
   const int l_knobWidth = 110;
   const int l_knobHeight = 110;
    // SMALL KNOB
   const int s_knobWidth = 80;
   const int s_knobHeight = 80;
    // COMBOBOX
   const int comboBoxWidth = 55;
   const int comboBoxHeight = 20;
   
    // OSC 1
    osc_1_SliderType.setBounds(10, 30, knobWidth, knobHeight);
    osc_1_SliderPitch.setBounds(10, 160, knobWidth, knobHeight);
    osc_1_SliderDetune.setBounds(10,290, knobWidth,knobHeight);
    // OSC 2
    osc_2_SliderType.setBounds(110, 30, knobWidth, knobHeight);
    osc_2_SliderPitch.setBounds(110, 160, knobWidth, knobHeight);
    osc_2_SliderDetune.setBounds(110,290, knobWidth,knobHeight);
    // FILTER SECTION
    filter_type_comboBox.setBounds(220, 265, comboBoxWidth + 10, comboBoxHeight);
    filter_SliderEG.setBounds(210, 310, s_knobWidth, s_knobHeight);
    filter_SliderCutoff.setBounds(210, 30,knobWidth ,knobHeight);
    filter_SliderResonance.setBounds(210, 160, knobWidth, knobHeight);
    // ENVELOPE SECTION
    attackSlider.setBounds(300,30,sliderWidth, sliderHeight);
    decaySlider.setBounds(350,30,sliderWidth, sliderHeight);
    sustainSlider.setBounds(400,30,sliderWidth, sliderHeight);
    releaseSlider.setBounds(450,30,sliderWidth, sliderHeight);
    // LFO SECTION
    lfo_SliderRate.setBounds(300, 275, l_knobWidth, l_knobHeight);
    lfo_SliderDepth.setBounds(410, 275, l_knobWidth, l_knobHeight);
    waveformComboBox.setBounds(382, 365, comboBoxWidth, comboBoxHeight);
    // FX SECTION
        //DISTORTION
    distortionSlider.setBounds(610, 25, l_knobWidth, s_knobHeight);
    distortion_ComboBox.setBounds(535, 25, comboBoxWidth + 25, comboBoxHeight);
    distortion_WetDry_Slider.setBounds(680, 25, l_knobWidth, s_knobHeight);
        // DELAY
    delay_TimeSlider.setBounds(505, 150,  l_knobWidth, s_knobHeight);
    delay_modulationSlider.setBounds(575, 150, s_knobWidth, s_knobHeight);
    delay_FeedbackSlider.setBounds(615, 150, l_knobWidth, s_knobHeight);
    delay_WetDrySlider.setBounds(755, 195, 50, 50);
    delay_grooveSlider.setBounds(705, 150, 85, 50);
    // OUTPUT/MASTER SECTION
    
    // MIXER
    osc1_volumeSlider.setBounds(520, 265, sliderWidth, 130);
    osc2_volumeSlider.setBounds(570, 265, sliderWidth, 130);
    oscNoise_volumeSlider.setBounds(620, 265, sliderWidth, 130);
    oscNoise_colour_Slider.setBounds(705, 265, 85, 20);
    
    // MASTER
    outputGainSlider.setBounds(725, 315, s_knobWidth, s_knobHeight);
    panSlider.setBounds(670, 315, s_knobWidth, s_knobHeight);
}



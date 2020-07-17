
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomColours.h"

//==============================================================================
/**
*/
class SynthTakeIiAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SynthTakeIiAudioProcessorEditor (SynthTakeIiAudioProcessor&);
    ~SynthTakeIiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthTakeIiAudioProcessor& processor;
    
    // ADSR SLIDERS
    Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    // OSC 1 SLIDERS
    Slider osc_1_SliderType, osc_1_SliderPitch, osc_1_SliderDetune;
    Label osc_1_SliderType_Label, osc_1_SliderPitch_Label, osc_1_SliderDetune_Label;
    // OSC 2 SLIDERS
    Slider osc_2_SliderType, osc_2_SliderPitch, osc_2_SliderDetune;
    Label osc_2_SliderType_Label, osc_2_SliderPitch_Label, osc_2_SliderDetune_Label;
    // FILTER SLIDERS
    Slider filter_SliderCutoff, filter_SliderResonance, filter_SliderEG;
    Label filter_SliderType_Label, filter_SliderCutoff_Label, filter_SliderResonance_Label, filter_SliderEG_Label;
    ComboBox filter_type_comboBox;
    Label filter_type_comboBox_Label;
    // LFO SLIDERS
    Slider lfo_SliderRate, lfo_SliderDepth;
    Label lfo_SliderRate_Label, lfo_SliderDepth_Label;
    ComboBox waveformComboBox;
    // DELAY FX SLIDERS
    Slider delay_TimeSlider;
    Slider delay_FeedbackSlider;
    Slider delay_WetDrySlider;
    Slider delay_modulationSlider;
    Slider delay_grooveSlider;
    
    Label delay_TimeSlider_Label;
    Label delay_FeedbackSlider_Label;
    Label delay_modulationSlider_Label;
    Label delay_WetDrySlider_Label;
    Label delay_grooveSlider_Label;
    
    
    // DISTORTION SLIDER
    Slider distortionSlider;
    Label distortionSlider_Label;
    
    Slider distortion_WetDry_Slider;
    Label distortion_WetDry_Slider_Label;
    
    // COMBOBOX DISTORTION TYPE
    ComboBox distortion_ComboBox;
    Label distortionType_Label;
    
    // OUTPUT GAIN SLIDER
    Slider outputGainSlider;
    Label outputGainLabel;
    
        // Mixer Sliders
    Slider osc1_volumeSlider;
    Slider osc2_volumeSlider;
    Slider oscNoise_volumeSlider;
    
    
    Label osc1_volumeSlider_Label;
    Label osc2_volumeSlider_Label;
    Label oscNoise_volumeSlider_Label;
    
    Slider oscNoise_colour_Slider;
    Label oscNoise_colour_Slider_Label;
        // PAN OUTPUT
    Slider panSlider;
    Label panLabel;
    
    // presetPanel
    // constructor presetPanel(presetPanel (*processor))
    // addAndmakeVisible
    // resized() give it bounds
    
    
    /*
     
     SLIDER ATTACHMENTS SECTION
    
     */
    
    
    
    // OSC1 ATTACHMENT
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1_wave_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1_pitch_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1_detune_sliderAttachment;
    
    // OSC2 ATTACHMENT
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2_wave_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2_pitch_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2_detune_sliderAttachment;
      
    
    // FILTER ATTACHMENT
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filter_type_ComboBox_Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filter_cutoff_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filter_resonance_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filter_eg_amount_slider_Attachment;
    
    // ADSR Attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attack_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decay_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustain_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> release_sliderAttachment;
    
    // LFO Sliders
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfo_rate_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfo_depth_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> lfo_waveform_comboBox_attachment;
    
    // FX & OUTPUT
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputGain_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pan_sliderAttachment;
        // DISTORTION
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> distortion_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> distortion_wetdry_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> distortion_ComboBox_Attachment;
        // DELAY
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delay_time_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delay_modulation_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delay_feedback_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delay_wetdry_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delay_groove_sliderAttachment;
    
        // MIXER Attachment
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc1_volume_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc2_volume_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscNoise_volume_sliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> osc_noise_volume_sliderAttachment;
    
    
    
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthTakeIiAudioProcessorEditor)
};

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Distortion.h"
#include "UtilityFunctions.h"
#include "Delay.h"

//==============================================================================
/**
*/
class SynthTakeIiAudioProcessor  : public AudioProcessor,
public ValueTree::Listener 
{
public:
    //==============================================================================
    SynthTakeIiAudioProcessor();
    ~SynthTakeIiAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float output_gain_multiplier { 0.5 };
    
    Synthesiser hw_Synth;
    SynthVoice* hw_Voice;
    
//    { new SynthVoice() }
    
    
//    Delay delay;
    Delay delay;
    Distortion delay_repeats_distortion;
    
    float delayFeedbackSample[2]; 
    
    
    
    Distortion hw_Distortion;
    
    double lastSampleRate;
    
    AudioProcessorValueTreeState apvts;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    void debugParams();

    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthTakeIiAudioProcessor)
    
};

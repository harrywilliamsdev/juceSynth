
#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Distortion.h"
#include "UtilityFunctions.h"
#include "Delay.h"
#include "SynthVoiceParams.h"
#include "SynthParameterLimits.h"
#include "Filter.h"

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
    
    void update();

    // Parameters
    SynthParameterLimits limits {0};
    SynthVoiceParameters params {0};
    // Synth object and pointer to voice
    Synthesiser hw_Synth;
    SynthVoice* hw_Voice;
    // Delay Objects
    Delay delay;
    Distortion delay_repeats_distortion;
    Filter delay_repeats_filter;
    
    float delayFeedbackSample[2] {0};
    float delay_wetdry_balance {0};
    float delay_groove {0};
    float delay_feedback {0};
    float delay_time {0};
    float delay_modulation {0};
    
    
    // Distortion
    Distortion hw_Distortion;
    float distortion_wetdry_balance {0};
    float distortion_amount {0};
    int distortion_type {0}; 
    
    
    
    
    
    // Pan params
    float left_pan {0};
    float right_pan {0};
    // Master output volume
    float output_gain {0};
    
    
    
    
    
    
    
    
    
    double lastSampleRate {0};
    
    AudioProcessorValueTreeState apvts;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    // Variables used in PluginProcessor process block
    // Declared here so can be updated in update()
    // Initialise using limits so params are correct from opening
    
    
    
    
    

    // Helper function, prints out the values in the APVTS
    void debugParams();

    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthTakeIiAudioProcessor)
    
    bool mustUpdateProcessing {false};
    
    void valueTreePropertyChanged(ValueTree& tree, const Identifier& property) override
    {
        mustUpdateProcessing = true;
        debugParams();
        
    }
    
    
    
    
};

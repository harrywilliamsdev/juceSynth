
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

    
    SynthParameterLimits limits;
    SynthVoiceParameters params;
    
    Synthesiser hw_Synth;
    SynthVoice* hw_Voice;
    
    Delay delay;
    Distortion delay_repeats_distortion;
    
    Filter delay_repeats_filter;
    
    float delayFeedbackSample[2];
    
    
    
    Distortion hw_Distortion;
    
    double lastSampleRate;
    
    AudioProcessorValueTreeState apvts;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    // Variables used in PluginProcessor process block
    // Declared here so can be updated in update()
    float distortion_wetdry_balance;
    float delay_wetdry_balance;
    
    float output_gain {limits.output_volume_default };
    
    
    

    
    void debugParams();

    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthTakeIiAudioProcessor)
    
    bool mustUpdateProcessing {false};
    
    void valueTreePropertyChanged(ValueTree& tree, const Identifier& property) override
    {
        mustUpdateProcessing = true;
        
    }
    
    
    
    
};

/*
  ==============================================================================

    SynthVoice.h
    Created: 7 Jun 2020 8:38:24pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "CustomColours.h"
#include "Maximilian.h"
#include "Osc.h"
#include "UtilityFunctions.h"
#include "SynthVoiceParams.h"

/*
 
 TO DO:
 
 GET Distortion Param in here.
 
 We need the apvts - 
 
 
 
 
 */


class SynthVoice : public SynthesiserVoice
{
    
public:
    SynthVoice (SynthVoiceParameters* params);
    
    void setCurrentPlaybackSampleRate (const double newRate) override; 


//==========================================================
    bool canPlaySound(SynthesiserSound* sound)
    {
        // Check if the type is a synth sound
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
//==========================================================
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        
       
        
       // Calculate frequency based on midi note number received
        frequency = midiNoteToFrequency(midiNoteNumber); // add steps
        // coarse offset the frequency using pitch
        osc_1_frequency = frequency_semitone_increase(frequency, parameters->osc_1_pitch);
        osc_2_frequency = frequency_semitone_increase(frequency, parameters->osc_2_pitch);
        
        
        
    }
    
//==========================================================
    
    void stopNote(float velocity, bool allowtailOff)
    {
        env1.trigger = 0;
        allowtailOff = true;
        
        
        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }
    
//==========================================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {
        
    }
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
       
        env1.setAttack(parameters->attack);
        env1.setDecay(parameters->decay);
        env1.setSustain(parameters->sustain);
        env1.setRelease(parameters->release);
        
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            
          // GENERATE SIGNALS
            
            // DETUNE PROCESSING
            
            float osc_1_detune_amount = 1 + (parameters->osc_1_detune / 1000);
            float osc_2_detune_amount = 1 + (parameters->osc_2_detune / 1000);
            
            
            double osc_signal = hw_osc_1.do_Oscillate(osc_1_frequency * osc_1_detune_amount, parameters->osc_1_wave); // add cents to pitch
            double osc2_signal = hw_osc_2.do_Oscillate(osc_2_frequency * osc_2_detune_amount, parameters->osc_2_wave);
            double oscNoise_signal = hw_osc_noise.do_Oscillate(frequency, 5);
            
            // Filter Noise
            
        //    oscNoise_signal = filter1.lores(oscNoise_signal, 2000, 1.1);
            
            
            // MIXER SECTION
                // ADJUST LEVELS
            osc_signal *= parameters->osc1_volume;
            osc2_signal *= parameters->osc2_volume;
            oscNoise_signal *= parameters->osc_noise_volume;
                // AND SUM TOGETHER
            double oscMixed = (osc_signal + osc2_signal + oscNoise_signal) * 0.33;
            
            
        // APPLY VOLUME ENVELOPE TO THE SIGNALS
            double oscEnv = env1.adsr(oscMixed, env1.trigger) * level;
        // RUN IT THROUGH A FILTER
            
            float filter_cutoff_target = parameters->filter_cutoff;
//
//            // IMPLEMENT THIS LATER
//            float filter_env = env1.adsr(filter_cutoff_target, env1.trigger) * parameters->filter_envelope_amount;
            
            double oscFilt = filter1.lores(oscEnv, filter_cutoff_target, parameters->filter_resonance);
            
            double outputSample = oscFilt;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, outputSample);
            }
            
            ++startSample;
        }
    }
    
public:
    
    double attack {130};
    double decay {100};
    double sustain {0.5};
    double release {400};
    
    

private:
  //  SynthTakeIiAudioProcessor& processor;
    
    double level;
    double frequency;
    
    double osc_1_frequency;
    double osc_2_frequency;
    
    float osc_1_cents;
    float osc_2_cents;
    
    maxiEnv env1;
    maxiFilter filter1;
    
    Oscillator hw_osc_1;
    Oscillator hw_osc_2;
    Oscillator hw_osc_noise;
    
    maxiSettings settings;
    
    SynthVoiceParameters* parameters;
  
    
 //   SynthTakeIiAudioProcessor& processor;
    
};

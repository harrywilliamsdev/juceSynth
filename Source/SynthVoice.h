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
#include "SynthParams.h"

/*
 
 TO DO:
 
 GET Distortion Param in here.
 
 We need the apvts - 
 
 
 
 
 
 
 
 
 
 */


class Dummy
{
public:
    Dummy(SynthParameters* params);
   
private:
    SynthParameters* parameters;
    
};


class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice (SynthParameters* params);
    
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
        frequency = midiNoteToFrequency(midiNoteNumber); // add steps
        
        
        
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
    
    // who knows how but this block will be??!
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
        env1.setAttack(parameters->attack);
        env1.setDecay(parameters->decay);
        env1.setSustain(parameters->sustain);
        env1.setRelease(parameters->release);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {

          // GENERATE SIGNALS
            double osc = hw_osc_1.do_Oscillate(frequency, 4); // add cents to pitch
            double osc2 = hw_osc_2.do_Oscillate((frequency /2 ), 2);
         //   double oscNoise = hw_osc_noise.do_Oscillate(frequency, 5) * 0.025;
            
        // APPLY VOLUME ENVELOPE TO THE SIGNALS
            // TEMPORARY MIX THEM TOGETHER
            double oscEnv = env1.adsr((osc + osc2) * 0.5, env1.trigger) * level;
        // RUN IT THROUGH A FILTER
            double oscFilt = filter1.lores(oscEnv, 6000, 1.1);
            
            double outputSample = oscFilt;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, outputSample);
            }
            
            ++startSample;
        }
    }
    
public:
    
//    double attack {130};
//    double decay {100};
//    double sustain {0.5};
//    double release {400};
    
    

private:
  //  SynthTakeIiAudioProcessor& processor;
    
    SynthParameters* parameters;
    double level;
    double frequency;
    
    maxiSettings settings;
    maxiEnv env1;
    maxiFilter filter1;
    
    Oscillator hw_osc_1;
    Oscillator hw_osc_2;
    Oscillator hw_osc_noise;
};

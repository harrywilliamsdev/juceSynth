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
#include "Filter.h"

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
    bool canPlaySound(SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowtailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
 
    
private:
    
    double level;
    double frequency;
    
    double osc_1_frequency;
    double osc_2_frequency;
    
    float osc_1_cents;
    float osc_2_cents;
    
    maxiEnv env1;
    maxiEnv filter_envelope;
    
    Oscillator hw_osc_1;
    Oscillator hw_osc_2;
    Oscillator hw_osc_noise;
    
    Filter hw_filter;
    Filter hw_noise_filter;
    
    maxiSettings settings;
    
    SynthVoiceParameters* parameters;
  
    
 //   SynthTakeIiAudioProcessor& processor;
    
};

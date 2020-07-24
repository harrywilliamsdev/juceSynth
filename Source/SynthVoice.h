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
#include "Osc.h"
#include "UtilityFunctions.h"
#include "SynthVoiceParams.h"
#include "Filter.h"
#include "LFO.h"
#include "Env.h"

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
    
    double level {0};
    double frequency {0};
    
    double osc_1_frequency {0};
    double osc_2_frequency {0};
    
    float osc_1_cents {0};
    float osc_2_cents {0};
    
    Envelope hw_envelope;
    Envelope hw_filter_envelope;
    
    Oscillator hw_osc_1;
    Oscillator hw_osc_2;
    Oscillator hw_osc_noise;
    
    LFO hw_lfo;
    
    Filter hw_filter;
    Filter hw_noise_filter;
    
    SynthVoiceParameters* parameters;
  
    
 //   SynthTakeIiAudioProcessor& processor;
    
};

/*
  ==============================================================================

    SynthVoiceParams.h
    Created: 11 Jul 2020 12:13:52am
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once


/*
 The purpose of this struct is to serve as a bridge between the AudioParameterValueTreeState object
 in the PluginProcessor, and the processing that takes places in the SynthVoice.
 */


struct SynthVoiceParameters
{
    // Envelope
    float attack { 100.f };
    float decay  { 50.f };
    float sustain { 0.8f };
    float release { 500.f };
    // Oscillator 1
    int osc_1_wave { 2 };
    int osc_1_pitch { 0 };
    float osc_1_detune { 0.f} ;
    // Oscillator 2
    int osc_2_wave { 2 };
    int osc_2_pitch { 0 };
    float osc_2_detune { 1.5f} ;
    // Filter
    int filter_type { 1 };
    float filter_cutoff { 2000.f };
    float filter_resonance  { 1.f };
    float filter_envelope_amount { 0 };
    
    // LFO
    int lfo_type {1};
    float lfo_rate {2};
    float lfo_pitch_depth {0};
    float lfo_filter_depth {0};
    
    // Mixer
    float osc1_volume { 1 };
    float osc2_volume { 1 };
    float osc_noise_volume { 0.05 };
    

};

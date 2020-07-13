/*
  ==============================================================================

    SynthVoiceParams.h
    Created: 11 Jul 2020 12:13:52am
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once


using floatType = double;

struct SynthVoiceParameters
{
    floatType attack { 100.f };
    floatType decay  { 50.f };
    floatType sustain { 0.8f };
    floatType release { 500.f };
    
    int osc_1_wave { 2 };
    int osc_1_pitch { 0 };
    float osc_1_detune { 0.f} ;
    
    int osc_2_wave { 2 };
    int osc_2_pitch { 0 };
    float osc_2_detune { 1.5f} ;
    
    int filter_type { 1 };
    float filter_cutoff { 2000.f };
    float filter_resonance  { 1.f };
    float filter_envelope_amount { 0 };
    
    // mixer
    
    float osc1_volume { 1 };
    float osc2_volume { 1 };
    float osc_noise_volume { 0.05 };
    

};

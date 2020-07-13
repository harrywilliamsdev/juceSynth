/*
  ==============================================================================

    SynthParameterLimits.h
    Created: 11 Jul 2020 5:41:01pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once

/*
 
 This struct holds all the values used to set up the parameters.
 Use this as the Master Location to change the range of params.
 
 In the processor, we create a SynthParameterLimits object, then take all
 the variables in the createParameters() method to set up our normalisable ranges
 
 They are all set as consts so they can't be accidentally changed somewhere else in the code.
  
 Each parameter should have a
 MIN, MAX, and DEFAULT
 */

struct SynthParameterLimits
{
    
    /*
     OSC PARAM LIMITS
     */
        // Osc Type
    const float osc_wave_min {1};
    const float osc_wave_max {4};
    const float osc_wave_default {2};
        // Osc Pitch
    const int osc_pitch_min {-12};
    const int osc_pitch_max {12};
    const int osc_pitch_default{0};
        // Osc Detune
    const float osc_detune_min{-50.f};
    const float osc_detune_max{50.f};
    const float osc_detune_default {0.f};
    
    /*
     FILTER PARAM LIMITS
     */
    
        // Filter Type
    const int filter_type_min {1};
    const int filter_type_max {2};
    const int filter_type_default {1};
        // Cutoff
    const float filter_cutoff_min {20};
    const float filter_cutoff_max {8000};
    const float filter_cutoff_default {2500};
        // Resonance
    const float filter_resonance_min {1.0};
    const float filter_resonance_max {3.0};
    const float filter_resonance_default {1.0};
    
    /*
     ADSR PARAM LIMITS
     */
        // ATTACK
    const float attack_min{0.01};
    const float attack_max{5000};
    const float attack_default{100};
        // DECAY
    const float decay_min{0.01};
    const float decay_max{5000};
    const float decay_default{50};
        // SUSTAIN
    const float sustain_min{0.01};
    const float sustain_max{0.99};
    const float sustain_default{0.8};
        // RELEASE
    const float release_min{0.01};
    const float release_max{5000};
    const float release_default{100};
    
    /*
     LFO PARAM LIMITS
     */
    
        // RATE
        
    const float lfo_min {0.0};
    const float lfo_max {10.f};
    const float lfo_default {0.2f};

    // DEPTH
    const float lfo_depth_min {0.0f};
    const float lfo_depth_max {5.0f};
    const float lfo_depth_default {1.f};
    // LFO WAVE
    const int lfo_wave_min {1};
    const int lfo_wave_max {3};
    const int lfo_wave_default {2};
    
    /*
     DISTORTION PARAMETER LIMITS
     */
    
};

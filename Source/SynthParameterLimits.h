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
    const int osc_wave_min {1};
    const int osc_wave_max {4};
    const int osc_wave_default {2};
        // Osc Pitch
    const int osc_pitch_min {-12};
    const int osc_pitch_max {12};
    const int osc_pitch_default{0};
        // Osc Detune
    const float osc_detune_min{0.99f};
    const float osc_detune_max{1.01f};
    const float osc_detune_default {1.f};
    
    /*
     FILTER PARAM LIMITS
     */
    
        // Filter Type
    const int filter_type_min {1};
    const int filter_type_max {3};
    const int filter_type_default {1};
        // Cutoff
    const float filter_cutoff_min {20};
    const float filter_cutoff_max {10000};
    const float filter_cutoff_default {2500};
        // Resonance
    const float filter_resonance_min {1.0};
    const float filter_resonance_max {3.0};
    const float filter_resonance_default {1.0};
    
    /*
     ADSR PARAM LIMITS
     */
        // ATTACK
    const float attack_min{};
    const float attack_max{};
    const float attack_default{};
        // DECAY
    const float decay_min{};
    const float decay_max{};
    const float decay_default{};
        // SUSTAIN
    const float sustain_min{};
    const float sustain_max{};
    const float sustain_default{};
        // RELEASE
    const float release_min{};
    const float release_max{};
    const float release_default{};
    
    /*
     LFO PARAM LIMITS
     */
    
        // RATE
    
        // DEPTH
    
        // LFO WAVE
    
    
    
    
    
    
    
};

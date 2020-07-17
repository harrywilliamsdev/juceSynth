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
    
        // Osc Type
    /*
         This parameter selects the waveform that the oscillator will produce
         1: Sine
         2: Triangle
         3: Square
         4: Saw
         5: Noise (Not accessable from GUI)
    */
    const float osc_wave_min {1};
    const float osc_wave_max {4};
    const float osc_wave_default {2};
        
        // Osc Pitch
    /*
        This parameter controls the coarse detune of each oscillator.
        It steps up in +- semitone intervals up to a maximum of 12 semitones (1 octave)
     */
    const int osc_pitch_min {-12};
    const int osc_pitch_max {12};
    const int osc_pitch_default{0};
        
        // Osc Detune
    /*
         This parameter controls the fine detune of each oscillator.
         It is a float based parameter with a finer resolution, meaning that the oscillator
         can be tuned to somewhere in between the standard semitone frequencies
    */
    const float osc_detune_min{-50.f};
    const float osc_detune_max{50.f};
    const float osc_detune_default {0.f};
    
    /*
     FILTER PARAM LIMITS
     */
    
        // Filter Type
    /*
        This parameter controls the hype of filter that is used,
        only two settings are available. 1 = Lowpass, 2 = Hipass
     
        The same biquad filter is used for each, but this parameter changes
        the way in which the coefficients are used, changing the profile of the filter.
     */
    const int filter_type_min {1};
    const int filter_type_max {3};
    const int filter_type_default {1};
        // Cutoff
    const float filter_cutoff_min {50};
    const float filter_cutoff_max {12000};
    const float filter_cutoff_default {8000};
        // Resonance
    const float filter_resonance_min {0.707};
    const float filter_resonance_max {0.7071};
    const float filter_resonance_default {0.707};
        // Filter ENV Amount
    const float filter_envelope_amount_min {0};
    const float filter_envelope_amount_max {1};
    const float filter_envelope_amount_default {0.0};
    
    
    /*
     ADSR PARAM LIMITS
     */
        // ATTACK
    /*
     This parameter controls the time (in ms) it takes for the signal being passed through it to reach
     maximum amplitude
     */
    const float attack_min{0.01};
    const float attack_max{5000};
    const float attack_default{100};
        // DECAY
    /*
     This parameter controls the time (in ms) it takes for the signal to 'decay' from its maximum amplitude, to the level set in the sustain portion of the envelope
     */
    const float decay_min{0.01};
    const float decay_max{3000};
    const float decay_default{50};
        // SUSTAIN
    /*
     The level at which the envelope 'sustains' while the key/trigger continues to be held down.
     This is a volume based parameter, not time based
     */
    const float sustain_min{0.01};
    const float sustain_max{0.99};
    const float sustain_default{0.8};
        // RELEASE
    /*
     This parameter controls the time in ms it takes for the envelope signal to
     decay down from the sustain value to 0 amplitude after the key is released
     */
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
    const float lfo_depth_max {100.f};
    const float lfo_depth_default {1.f};
    // LFO WAVE
    const int lfo_wave_min {1};
    const int lfo_wave_max {3};
    const int lfo_wave_default {2};
    
    /*
     DISTORTION PARAMETER LIMITS
     */
    
    const float distortion_amount_min {0.001};
    const float distortion_amount_max {3};
    const float distortion_amount_default {1.f};
    
    const int distortion_type_min {1};
    const int distortion_type_max {4};
    const int distortion_type_default {3};
    
    const float distortion_wetdry_min {0.0};
    const float distortion_wetdry_max {1.0};
    const float distortion_wetdry_default {0.0};
    
    /*
     DELAY PARAMETER LIMITS
     */
    
    const float delay_time_min {0};
    const float delay_time_max {1500};
    const float delay_time_default {200};
    
    const float delay_feedback_min {0.f};
    const float delay_feedback_max {2.f};
    const float delay_feedback_default {0.33};
    
    const float delay_modulation_min {0.01f};
    const float delay_modulation_max {10.f};
    const float delay_modulation_default {2.f};
    
    const float delay_groove_min {-0.5f};
    const float delay_groove_max {2.f};
    const float delay_groove_default {1.0};
    
    const float delay_wetdry_min {0};
    const float delay_wetdry_max {1.0};
    const float delay_wetdry_default {0};
    
    /*
     MIXER PARAMETER LIMITS
     */
    
    const float osc_volume_min {0.0};
    const float osc_volume_max {1.0};
    const float osc_pitched_volume_default {0.5};
    const float osc_noise_volume_default {0};
    
    const float output_volume_min {0.0};
    const float output_volume_max {1.0};
    const float output_volume_default {0.75};
    
    const float output_pan_min {0};
    const float output_pan_max {1};
    const float output_pan_default {0.5};
    
    
    
    
    
    
};

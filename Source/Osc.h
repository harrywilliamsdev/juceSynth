/*
  ==============================================================================

    Osc.h
    Created: 7 Jun 2020 10:29:46pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include <cmath>
#include "UtilityFunctions.h"
#include <JuceHeader.h>

#define EXTRACT_BITS(the_val, bits_start, bits_len) ((the_val >> (bits_start - 1)) & ((1 << bits_len) - 1))


class Oscillator
{
    double frequency;
    double phase;
    double increment;
    double output;
    double m_sample_rate { 44100 };
    
    
public:
    Oscillator();
    double do_Oscillate(double frequency, int oscType);
    double generate_sinewave(double frequency);
    double generate_triangle(double frequency);
    double generate_saw(double frequency);
    double generate_square(double frequency);
    double generate_noise();
    double generate_pn_noise(unsigned int uPNRegister);
    
    // HELPERS
    
    double calculate_increment(double frequency, double sampleRate);
    void check_modulo();
    
};

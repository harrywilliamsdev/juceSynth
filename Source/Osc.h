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



class Oscillator
{
    double frequency {0};
    double phase {0};
    double increment{0};
    double output{0};
    double sample_rate { 44100 };
    
    
public:
    Oscillator();
    double do_Oscillate(double frequency, int oscType);
    double generate_sinewave(double frequency);
    double generate_triangle(double frequency);
    double generate_saw(double frequency);
    double generate_square(double frequency);
    double generate_noise();
    double generate_pseudorandom_noise();
};

/*
  ==============================================================================

    LFO.h
    Created: 16 Jul 2020 5:34:57pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include "UtilityFunctions.h"
#include <JuceHeader.h>



class LFO
{
    float rate {0};
    float phase {0};
    float increment{0};
    float output{0};
    float sample_rate { 44100 };
    
    
public:
    LFO();
    void check_modulo_counter();
    void calculate_increment(); 
    float do_Oscillate(float rate, int oscType);
    float generate_sinewave(float rate);
    float generate_triangle(float rate);
    float generate_square(float rate);
};

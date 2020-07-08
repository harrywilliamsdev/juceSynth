/*
  ==============================================================================

    Osc.cpp
    Created: 7 Jun 2020 10:29:46pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "Osc.h"
#include <cmath>
#include <JuceHeader.h>
#include "UtilityFunctions.h"


Oscillator::Oscillator()
{
    phase = 0.0;
}


double Oscillator::generate_sinewave(double frequency)
{
    increment = (1 / (m_sample_rate / frequency));
    output = sin(phase*(TWOPI));
    // Wrap around the modulo counter
    if (phase >= 1.0)
    {
        phase -= 1.0;
    }
    phase += increment;
    return (output);
}

double Oscillator::generate_triangle(double frequency)
{
    // Calculate Phase Inc
    increment = (1 / (m_sample_rate / frequency));
    // Modulo wrap
    if (phase >= 1.0) phase -= 1.0;
    
    // Generate output
    if (phase <= 0.5)
    {
        output = (phase - 0.25) * 4;
    }
    else
    {
        output = ((1.0 - phase) - 0.25 ) * 4;
    }
    // Inc phase
    phase += increment;
    // Output
    return output; 
}

double Oscillator::generate_saw(double frequency)
{
    // Calculate phase inc
    increment = (1 / (m_sample_rate / frequency));
    
    output = phase;
    if (phase >= 1.0)
    {
        phase -= 2.0;
    }
    phase +=increment;
    
    return output; 
}

double Oscillator::generate_square(double frequency)
{
    increment = (1 / (m_sample_rate / frequency));
    // calculate output
    if (phase < 0.5)
    {
        output = -1.0;
    }
    else
    {
        output = 1.0; 
    }
    // check modulo wrap
    if (phase >= 1.0)
    {
        phase -= 1.0;
    }
    // recalculate inc amount, and increment
    phase += increment;
    
    return output;
}

double Oscillator::generate_noise()
{
    float randValue = rand()/(float)RAND_MAX;
    output = randValue*2 -1;
    return(output);
}

double Oscillator::do_Oscillate(double frequency, int oscType)
{
    switch(oscType)
    {
        case 1:
            output = generate_sinewave(frequency);
            break;
        case 2:
            output = generate_triangle(frequency);
            break;
        case 3:
            output = generate_square(frequency);
            break;
        case 4:
            output = generate_saw(frequency);
            break;
        case 5:
            output = generate_noise();
    }
    
    return output;
}



/*
  ==============================================================================

    Osc.cpp
    Created: 7 Jun 2020 10:29:46pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "Osc.h"
#include <JuceHeader.h>

Oscillator::Oscillator()
{
    phase = 0.0;
}


double Oscillator::generate_sinewave(double frequency)
{
    increment = (1 / (sample_rate / frequency));
    // Wrap around the modulo counter
    if (phase >= 1.0)
    {
        phase -= 1.0;
    }
    output = sin(phase*(TWOPI));
    phase += increment;
    return (output);
}

double Oscillator::generate_triangle(double frequency)
{
    // Calculate Phase Inc
    increment = (1 / (sample_rate / frequency));
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
    increment = (1 / (sample_rate / frequency));
    
    if (phase >= 1.0)
    {
        phase -= 2.0;
    }
    output = phase;
    phase +=increment;
    
    return output; 
}

double Oscillator::generate_square(double frequency)
{
    increment = (1 / (sample_rate / frequency));
    // check modulo wrap
    if (phase >= 1.0)
    {
        phase -= 1.0;
    }
    // calculate output
    if (phase < 0.5)
    {
        output = -1.0;
    }
    else
    {
        output = 1.0;
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
            break;
        
    }
    
    return output;
}



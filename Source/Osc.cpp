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
    increment = (1 / (m_sample_rate / frequency));
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
    increment = (1 / (m_sample_rate / frequency));
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

double Oscillator::generate_pn_noise(unsigned int uPNRegister)
{
    // get the bits from the seed value
    unsigned int b0 = EXTRACT_BITS(uPNRegister, 1, 1);
    unsigned int b1 = EXTRACT_BITS(uPNRegister, 2, 1);
    unsigned int b27 = EXTRACT_BITS(uPNRegister, 28, 1);
    unsigned int b28 = EXTRACT_BITS(uPNRegister, 29, 1);
    
    // create an XOR
    
    unsigned int b31 = b0^b1^b27^b28;
    
    // form the mask to OR with the register to load b31
    
    if (b31 == 1 )
    {
        b31 = 0x10000000;
        
    }
    
    // shift one bit to the right
    uPNRegister >>= 1;
    
    // set the bit
    
    uPNRegister |= b31;
    
    // convert to float
    float fOut = (float)(uPNRegister)/((std::pow((float)2.0, (float)32.0)) / 16.0 );
    
    // scale
    
    fOut -= 1.0;
    
    return fOut;
    
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
        case 6:
            output = generate_pn_noise(frequency);
            break;
        
    }
    
    return output;
}



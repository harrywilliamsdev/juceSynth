/*
  ==============================================================================

    LFO.cpp
    Created: 16 Jul 2020 5:34:57pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "LFO.h"


LFO::LFO()
{
    phase = 0;
}

float LFO::generate_sinewave(float rate)
{
   increment = (1 / (sample_rate / rate));
   // Wrap around the modulo counter
   if (phase >= 1.0)
   {
       phase -= 1.0;
   }
   output = sin(phase*(TWOPI));
   phase += increment;
   return (output);
}

float LFO::generate_triangle(float rate)
{
   // Calculate Phase Inc
      increment = (1 / (sample_rate / rate));
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


float LFO::generate_square(float rate)
{
   increment = (1 / (sample_rate / rate));
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

float LFO::do_Oscillate(float rate, int oscType)
{
    
    switch (oscType)
    {
        case 1:
        {
            output = generate_sinewave(rate);
            break;
        }
            
        case 2:
        {
            output = generate_triangle(rate);
            break;
        }
            
        case 3:
        {
            output = generate_square(rate);
            break;
        }
    }
    
    return output;
}

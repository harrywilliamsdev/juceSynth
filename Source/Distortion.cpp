/*
  ==============================================================================

    Distortion.cpp
    Created: 9 Jun 2020 12:12:42am
    Author:  Harry Williams

  ==============================================================================
*/

#include "Distortion.h"
#include <cmath>
 
Distortion::Distortion()
{
    
}

Distortion::~Distortion()
{
    
}

double Distortion::processSample(double input_sample, double saturation_amount, int type)
{
    double output;
    
    switch (type)
    {
            // Hyperolic Tangent Waveshaper
        case 1:
            output = std::tanh(saturation_amount * sin(input_sample)) / std::tanh(saturation_amount);
            break;
            // Arctangent Waveshaper
        case (2):
            output = atan(saturation_amount*input_sample) / atan(saturation_amount);
            break;
            // Sigmoid Waveshaper
        case (3):
            output = 2 * (1 / (1 + exp(-saturation_amount * input_sample))) - 1;
            break;
//            // Fuzz Waveshaper
        case (4):
            float k_x = std::abs(saturation_amount * input_sample);
            output = signum(input_sample) * (1 - std::exp(-k_x)) / (1 - std::exp(-saturation_amount));
            break;
    }
    
    return output;
    
}




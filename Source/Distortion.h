/*
  ==============================================================================

    Distortion.h
    Created: 9 Jun 2020 12:12:42am
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include "UtilityFunctions.h"


class Distortion
{
public:
    
    Distortion();
    ~Distortion();
    
    double processSample(double input_sample, double gain_multiplier, int type);
    
    float euler = 2.71828;

    
};

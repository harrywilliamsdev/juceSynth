/*
  ==============================================================================

    SynthParams.h
    Created: 10 Jul 2020 10:29:20am
    Author:  Jose Diaz

  ==============================================================================
*/

#pragma once

using floatType = double;

struct SynthParameters
{
    
    //ADSR
    floatType attack {130.f};
    floatType decay {100.f};
    floatType sustain {0.5};
    floatType release {400.f};
};

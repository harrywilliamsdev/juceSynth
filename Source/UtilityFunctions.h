/*
  ==============================================================================

    UtilityFunctions .h
    Created: 7 Jun 2020 10:33:37pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#define PI  3.1415926535897932384626433832795
#define TWOPI 6.283185307179586476925286766559



inline double midiNoteToFrequency(int midiNote)
{
    const double ratio = std::pow(2.0, 1.0 / 12.0);
    
    // Calc middle c pitch (3 semitones above a4)
    const double c5 = 220.0 * std::pow(ratio, 3);
    // Calc c0 pitch (5 octaves below middle c)
    const double c0 = c5 * std::pow(0.5, 5);
    // 
    double frequency = c0 * std::pow(ratio, midiNote);
    
    return frequency;
}

inline double frequency_semitone_increase(float in_frequency, int semitones)
{
    const double ratio = std::pow(2.0, 1.0 / 12);
    
    double out_frequency = in_frequency  * std::pow(ratio, semitones);
    
    return out_frequency; 
}



inline int convert_ms_to_samples(int milliseconds)
{
    return milliseconds * 44100;
}

// Used to convert Modulo ramp into expo decay waveform.
inline float concave_inverted_transform(float input)
{
    float LIMIT = 0.00398107;
    if (input <= LIMIT)
        return 1.0;
    
    return -(5.0/12.0)*std::log10(input);
}





inline float linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t  * v1;
}

inline int signum(float x)
{
    if (x >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

inline float convert_degrees_to_radians (float degrees)
{
    float radians = degrees * PI / 180;
    return radians;
}

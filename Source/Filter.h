/*
  ==============================================================================

    Filter.h
    Created: 15 Jul 2020 12:55:41am
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once

class Filter
{
public:
    
    Filter();
    ~Filter();
    
    float process_sample(float input, float cutoff, float resonance, int type);
    void calculate_biquad_coefficients();
    
    float x1;
    float x2;
    float y1;
    float y2;
    
    float b0 {1.f};
    float b1 {0.f};
    float b2 {0.f};
    
    float a0 {1.f};
    float a1 {0.f};
    float a2 {0.f};
    
    float frequency {8000};
    const float Q = 0.5;
    
    float sampleRate {44100};
    
    
};

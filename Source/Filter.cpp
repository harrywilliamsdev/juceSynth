/*
  ==============================================================================

    Filter.cpp
    Created: 15 Jul 2020 12:55:41am
    Author:  Harry Williams

  ==============================================================================
*/

#include "Filter.h"
#include "UtilityFunctions.h"

Filter::Filter()
{
    
}

Filter::~Filter()
{
    
}

float Filter::process_sample(float x, float cutoff, int type)
{
    
    if (cutoff != last_cutoff)
        should_recalculate_coefficients = true;
    
    if (should_recalculate_coefficients)
    {
        // frequency to w0
        float w0 = TWOPI * cutoff / sampleRate;
        // calculate alpha
        float alpha = (sin(w0) * Q) / 2;
        // Calculate cos w0
        float cos_w0 = cos(w0);
        
        switch (type)
        {
                // LPF calculation
            case 1:
            {
                a0 = 1.f + alpha;
                b0 = (1.f - cos_w0) / 2;
                b1 = 1.f - cos_w0;
                b2 = b1;
                
                a1 = -2.f * cos_w0;
                a2 = 1.f - alpha;
                break;
            }
                // HPF Calculation
            case 2:
            {
                // Q =
                
//                a0 = 1.f + alpha;
//                b0 = 1 + cos_w0 / 2;
//                b1 = -(1 + cos_w0);
//                b2 = 1 + cos_w0 / 2;
//                a1 = -2 * cos_w0;
//                a2 = 1.f - alpha;
//                break;
                
                
                a0 = 1.f + alpha;
                b0 = 1;
                b1 = -2 * cos_w0;
                b2 = 1;
                a1 = -2 * cos_w0;
                a2 = 1 - alpha;
                break;
                
            }
                // BPF/Peaking Calculation
            case 3:
            {
                a0 = 1.f + alpha;
                b0 = alpha;
                b1 = 0;
                b2 = -alpha;
                a1 = -2 * cos_w0;
                a2 = 1 - alpha;
                break;
            }
                // NOTCH FILTER
            case 4:
            {
                a0 = 1.f + alpha;
                b0 = 1;
                b1 = -2 * cos_w0;
                b2 = 1;
                a1 = -2 * cos_w0;
                a2 = 1 - alpha;
                break;
            }
    }
    
            // DIVIDE ALL THROUGH A0
        b0 /= a0;
        b1 /= a0;
        b2 /= a0;
        a1 /= a0;
        a2 /= a0;
    
        should_recalculate_coefficients = false;
    
    }
    float y;
    
    y = b0 * b1 * x1 + b2 * x2 + (-a1) * y1 + (-a2) * y2;
    
    // update unit delay samples
    x2 = x1;
    x1 = x;
    y2 = y1;
    y1 = y;
    
    last_cutoff = cutoff;
    
    return y;
}

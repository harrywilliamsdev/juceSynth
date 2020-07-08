/*
  ==============================================================================

    Delay.cpp
    Created: 2 Jul 2020 11:58:34am
    Author:  Harry Williams

  ==============================================================================
*/

#include "Delay.h"


Delay::Delay(){
}

Delay::Delay(float delay,float speed){
    this->delay = delay;
    this->speed = speed;
}

// Destructor
Delay::~Delay(){
}


float Delay::processSample(float x, int channel, float stereoRatio){
    
    if (channel == 1)
    {
        
        delay *= stereoRatio;
    }
    
    
    if (delay < 1.f){
        return x;
    }
    else{
        float lfo;
        
        lfo = depth * sin(currentAngle[channel]);
        
        currentAngle[channel] += angleChange;
        if (currentAngle[channel] > 2.f * M_PI){
            currentAngle[channel] -= 2.f * M_PI;
        }
                    
        // Delay Buffer
        // "delay" can be fraction
        int d1 = floor(delay+lfo);
        int d2 = d1 + 1;
        float g2 = delay + lfo - (float)d1;
        float g1 = 1.0f - g2;
        
        int indexD1 = index[channel] - d1;
        if (indexD1 < 0){
            indexD1 += MAX_BUFFER_SIZE;
        }
        
        int indexD2 = index[channel] - d2;
        if (indexD2 < 0){
            indexD2 += MAX_BUFFER_SIZE;
        }
        
        float y = g1 * delayBuffer[indexD1][channel] + g2 * delayBuffer[indexD2][channel];
        
        delayBuffer[index[channel]][channel] = x;
        
        if (index[channel] < MAX_BUFFER_SIZE - 1){
            index[channel]++;
        }
        else{
            index[channel] = 0;
        }
        
        return y;
    }
}

void Delay::setFs(float Fs){
    this->Fs = Fs;
}


void Delay::setDelaySamples(float delay){
    if (delay >= 1.f){
        this->delay = delay;
    }
    else{
        this->delay = 0.f;
    }
}


void Delay::setSpeed(float speed){
    if (speed >= 0.1f && speed <= 10.0f){
        this->speed = speed;
        angleChange = speed * (1.f/Fs) * 2 * M_PI;
    }
}

void Delay::setDepth(float depth){

    this->depth = depth;
}

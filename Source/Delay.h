/*
  ==============================================================================

    Delay.h
    Created: 2 Jul 2020 11:58:34am
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once


#include <cmath>
using namespace std;

class Delay {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Delay();
    
    Delay(float delay, float speed);
    
    // Destructor
    ~Delay();
    
    float processSample(float x,int channel, float stereoRatio);

    void setFs(float Fs);
    
    void setDelaySamples(float delay);
    
    void setSpeed(float speed);
    void setDepth(float depth);

    
private:
    
    float Fs = 44100.f;
    
    float delay = 450.f;
    
    const int MAX_BUFFER_SIZE = 88200;
    float delayBuffer[88200][2] = {0.0f};
    int index[2] = {0};
    
    float speed = 5.0f; // Hz, frequency of LFO
    float depth = 10.0f; // percentage of intensity, control amp of LFO
    
    float currentAngle[2] = {0.0f};
    float angleChange = speed * (1.f/Fs) * 2.f * M_PI;
    
    
    
};



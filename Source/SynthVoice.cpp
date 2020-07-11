/*
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Jun 2020 10:46:34pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "SynthVoice.h"


SynthVoice::SynthVoice(SynthVoiceParameters* params) : parameters (params)
{
    
}

void SynthVoice::setCurrentPlaybackSampleRate(const double newRate)
{
    settings.setSampleRate(newRate);
    SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);
}

/*
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Jun 2020 10:46:34pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "SynthVoice.h"


//SynthVoice::SynthVoice(SynthTakeIiAudioProcessor& p):
//processor(p)
//{
//
//}


Dummy::Dummy(SynthParameters* params) : parameters(params)
{
    
}

SynthVoice::SynthVoice(SynthParameters* params) : parameters(params)
{
    
}

void SynthVoice::setCurrentPlaybackSampleRate (const double newRate)
{
    settings.setSampleRate(newRate);

    SynthesiserVoice::setCurrentPlaybackSampleRate (newRate);
}

/*
  ==============================================================================

    Env.cpp
    Created: 17 Jul 2020 1:52:54pm
    Author:  Harry Williams

  ==============================================================================
*/

#include "Env.h"

double Envelope::adsr(double input,  int trigger)
{

    if (trigger==1 && attackphase!=1 && holdphase!=1 && decayphase!=1){
        holdcount=0;
        decayphase=0;
        sustainphase=0;
        releasephase=0;
        attackphase=1;
    }

    if (attackphase==1) {
        releasephase=0;
        amplitude+=(1*attack);
        output=input*amplitude;

        if (amplitude>=1) {
            amplitude=1;
            attackphase=0;
            decayphase=1;
        }
    }


    if (decayphase==1) {
        output=input*(amplitude*=decay);
        if (amplitude<=sustain) {
            decayphase=0;
            holdphase=1;
        }
    }

    if (holdcount<holdtime && holdphase==1) {
        output=input*amplitude;
        holdcount++;
    }

    if (holdcount>=holdtime && trigger==1) {
        output=input*amplitude;
    }

    if (holdcount>=holdtime && trigger!=1) {
        holdphase=0;
        releasephase=1;
    }

    if (releasephase==1 && amplitude>0.) {
        output=input*(amplitude*=release);

    }

    return output;
}

void Envelope::setAttack(double attackMS)
{
    attack = 1-std::pow( 0.01, 1.0 / ( attackMS * sampleRate * 0.001 ) );
    
//=======================================
    // PIRKLE METHOD
    
//    float samples = sampleRate * ((attackMS) / 1000);
//    float attack_coefficient = std::exp(-std::log((1.0 + attack_TCO) / attack_TCO) / samples);
//    float attack_offset = (1.0 + attack_TCO) * (1.0 - attack_coefficient);
//    attack = attack_offset;
    
    
}

void Envelope::setRelease(double releaseMS)
{
    release = std::pow( 0.01, 1.0 / ( releaseMS * sampleRate * 0.001 ) );
    
    //=======================================
    // PIRKLE METHOD
    
//
//    float samples = sampleRate * (releaseMS / 1000);
//    float release_coefficent = std::exp(-std::log((1.0 + release_TCO) / release_TCO) / samples);
//    float release_offset = -release_TCO * (1.0 - release_coefficent);
//    release = release_offset;
    
}

void Envelope::setSustain(double sustainL)
{
    sustain = sustainL;
    
    //=======================================
    // PIRKLE METHOD
}

void Envelope::setDecay(double decayMS)
{
    decay = std::pow( 0.01, 1.0 / ( decayMS * sampleRate * 0.001 ) );

    
    // ALT METHOD
//    float samples = sampleRate * (decayMS / 1000);
//    float decay_coefficient = std::exp(-std::log((1.0 + decay_TCO) / decay_TCO) / samples);
//    float decay_offset = (sustain - decay_TCO) * (1.0 - decay_coefficient);
//    decay = decay_offset;
    
    
}

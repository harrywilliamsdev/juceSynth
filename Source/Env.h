/*
  ==============================================================================

    Env.h
    Created: 17 Jul 2020 1:52:54pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once


/*
 This class is taken from the open source library Maximillian.
 Credit to 
 */

class Envelope {
    
public:
    double adsr(double input, int trigger=0);
    double input;
    double output;
    double attack;
    double decay;
    double sustain;
    double release;
    double amplitude;
    float sampleRate { 44100 };

    void setAttack(double attackMS);
    void setRelease(double releaseMS);
    void setDecay(double decayMS);
    void setSustain(double sustainL);
    int trigger;

    long holdtime=1;
    long holdcount;
    int attackphase,decayphase,sustainphase,holdphase,releasephase;


    // ------------------------------------------------
    // getters/setters
    int getTrigger() const{
        return trigger;
    }

    void setTrigger(int trigger){
        this->trigger = trigger;
    }

    // ------------------------------------------------
};
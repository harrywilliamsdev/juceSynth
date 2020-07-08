/*
  ==============================================================================

    SynthSound.h
    Created: 7 Jun 2020 8:38:14pm
    Author:  Harry Williams

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
    
    bool appliesToNote(int midiNoteNumber)
    {
        return true;
    }
    
    bool appliesToChannel(int midiChannel)
    {
        return true;
    }
};

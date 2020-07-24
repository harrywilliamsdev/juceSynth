/*
  ==============================================================================

    CustomSlider.cpp
    Created: 24 Jul 2020 10:14:31am
    Author:  Jose Diaz

  ==============================================================================
*/

#include "CustomSlider.h"


CustomSlider::CustomSlider (AudioProcessorValueTreeState& stateToControl,
                            String parameterID) : parameterAttachment (stateToControl, parameterID, *this)
{
    
    
    /// set up your text box here
    
}


MidiAssignableSlider::MidiAssignableSlider (AudioProcessorValueTreeState& stateToControl,
                                            String parameterID,
                                            SynthTakeIiAudioProcessor& proc)
: CustomSlider (stateToControl, parameterID), processor (proc)
{
    
}

void MidiAssignableSlider::mouseDown (const MouseEvent &e)
{
    if (e.mods.isCommandDown())
    {
        assignToCC();
        
    }
    
}

void MidiAssignableSlider::assignToCC()
{
    // wait until cc?
    // try to assign cc to controllerAssignment
    // processor.ccFIFO.pull() ????
    // updateCCTree (cc, parameterID)
    // if assignment happens, isAssigned = true;
}


void MidiAssignableSlider::updateCCTree()
{
    // find entry for CC
        // populate field with parameter id
        // remove param id from any other mapping
    
    
}

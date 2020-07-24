/*
  ==============================================================================

    CustomSlider.h
    Created: 24 Jul 2020 10:14:31am
    Author:  Jose Diaz

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"


class CustomSlider : public Slider
{
public:
    CustomSlider (AudioProcessorValueTreeState& stateToControl, String parameterID);

    String parameterID;
protected:
    AudioProcessorValueTreeState::SliderAttachment parameterAttachment; // HEAP ALLOCATE??????
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider);
};

class MidiAssignableSlider : public CustomSlider
{
public:
    MidiAssignableSlider (AudioProcessorValueTreeState& stateToControl,
                          String parameterID,
                          SynthTakeIiAudioProcessor& proc);
    
    // some mouse stuff
    
    // assign to cc
    void assignToCC ();
    
    void updateCCTree();
    
    void mouseDown (const MouseEvent &e);
    
private:
    bool isAssigned = false;
    int controllerAssignment = 0;
    SynthTakeIiAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiAssignableSlider);
};









// Custom Slider
    // Decorator for midi learn
            // override Slider::mouseDown
                    // if e.isRightClick
                        // wait for next midi message
                            // check if that message is valid
                                // Check the controller number of that message
                                // Is that number free?

/*
 
    Check Midi somewhere
    Get knob assignments
    
    
    when each knob moves->
        get value (0-127), remap to param range
        param->setValueNotifyingHost
 
 
    can we grab midi messages outside of the synth in process block?
 
    processBlock::()
        for (parseMidiEvents()
     {
        if event = assigned CC
            grab the associated param and change it
     }
        
 
 
 
 */



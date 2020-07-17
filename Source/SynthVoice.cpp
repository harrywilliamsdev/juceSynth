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
    /*
     *The hosts sample rate is used in a number of the equations,
     including the oscillators increment calculation and the biquad calculations
     */
    hw_filter.sampleRate = newRate;
    SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);
    hw_envelope.sampleRate = newRate;
    hw_filter_envelope.sampleRate = newRate; 
}

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
    // Check if the type is a synth sound
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}


// This method is triggered when a midi note is received.
// The midi event may come from a keyboard, DAW, or Game Engine
void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    // Set the envelope trigger flags
    hw_envelope.trigger = 1;
    hw_filter_envelope.trigger = 1;
    level = velocity;
     
    // Calculate frequency based on midi note number received
     frequency = midiNoteToFrequency(midiNoteNumber); // add steps
     // coarse offset the frequency using pitch
     osc_1_frequency = frequency_semitone_increase(frequency, parameters->osc_1_pitch);
     osc_2_frequency = frequency_semitone_increase(frequency, parameters->osc_2_pitch);
     
     
}

void SynthVoice::stopNote(float velocity, bool allowtailOff)
{
    hw_envelope.trigger = 0;
    allowtailOff = true;
    
    
    if (velocity == 0)
    {
        clearCurrentNote();
    }
    
    
    hw_lfo.setPhase(0);
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    // BLOCK BASED PROCESSING
        /*
            Some parameter updates can be done on a block-by-block basis
            The block size is set by the host. Common sizes include 64, 128, 256, 512, etc samples
         
            Suppose the sample rate of the system is 44100Hz. This would update 44100
            times per second. With a block size of 512, these updates would only occur
            86 times per second
         */
            hw_envelope.setAttack(parameters->attack);
            hw_envelope.setDecay(parameters->decay);
            hw_envelope.setSustain(parameters->sustain);
            hw_envelope.setRelease(parameters->release);
    
            hw_filter_envelope.setAttack(parameters->attack);
            hw_filter_envelope.setDecay(parameters->decay);
            hw_filter_envelope.setSustain(parameters->sustain);
            hw_filter_envelope.setRelease(parameters->release);
    
            for (int sample = 0; sample < numSamples; ++sample)
            {
                
              
                // DETUNE PREPROCESSING
                
                float osc_1_detune_amount = 1 + (parameters->osc_1_detune / 1000);
                float osc_2_detune_amount = 1 + (parameters->osc_2_detune / 1000);
                
                    // LFO DETUNE
                float lfo_signal = hw_lfo.do_Oscillate(parameters->lfo_rate, parameters->lfo_type);
                float lfo_pitch_amount = lfo_signal * parameters->lfo_pitch_depth;
                
                // GENERATE SIGNALS
                double osc_signal = hw_osc_1.do_Oscillate((osc_1_frequency * osc_1_detune_amount) + lfo_pitch_amount , parameters->osc_1_wave);
                double osc2_signal = hw_osc_2.do_Oscillate((osc_2_frequency * osc_2_detune_amount) + lfo_pitch_amount, parameters->osc_2_wave);
                double oscNoise_signal = hw_osc_noise.do_Oscillate(frequency, 5);
                
                
                // MIXER SECTION
                    // ADJUST LEVELS
                osc_signal *= parameters->osc1_volume;
                osc2_signal *= parameters->osc2_volume;
                oscNoise_signal *= parameters->osc_noise_volume;
                    // AND SUM TOGETHER
                double oscMixed = (osc_signal + osc2_signal + oscNoise_signal) * 0.5;
                
                
            // APPLY VOLUME ENVELOPE TO THE SIGNALS
                double oscEnv = hw_envelope.adsr(oscMixed, hw_envelope.trigger) * level;
            // FILTER PREPROCESSING
                // Cutoff knob value from gui
                float filter_cutoff_target = parameters->filter_cutoff;
    
                
                // runs cutoff knob value through an envelope ramp
                float filter_env = (filter_cutoff_target / 4 ) + (hw_filter_envelope.adsr(filter_cutoff_target, hw_envelope.trigger) * parameters->filter_envelope_amount);
                
                // limit the range of the filter
                if (filter_env >= 18000)
                {
                    filter_env = 18000;
                }
                
                if (filter_env <= 50)
                {
                    filter_env = 50;
                }
                
                // filter the sound
                double oscFilt = hw_filter.process_sample(oscEnv, filter_env, parameters->filter_resonance, parameters->filter_type);
                
                // set the output sample
                double outputSample = oscFilt;
                
                // fill the buffer with samples
                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {
                    outputBuffer.addSample(channel, startSample, outputSample);
                }
                
                ++startSample;
            }
}



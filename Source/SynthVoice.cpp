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
    hw_filter.sampleRate = newRate;
    SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);
}

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
    // Check if the type is a synth sound
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    env1.trigger = 1;
    filter_envelope.trigger = 1;
    level = velocity;
     
    // Calculate frequency based on midi note number received
     frequency = midiNoteToFrequency(midiNoteNumber); // add steps
     // coarse offset the frequency using pitch
     osc_1_frequency = frequency_semitone_increase(frequency, parameters->osc_1_pitch);
     osc_2_frequency = frequency_semitone_increase(frequency, parameters->osc_2_pitch);
     
     
}

void SynthVoice::stopNote(float velocity, bool allowtailOff)
{
    env1.trigger = 0;
    allowtailOff = true;
    
    
    if (velocity == 0)
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
            env1.setAttack(parameters->attack);
            env1.setDecay(parameters->decay);
            env1.setSustain(parameters->sustain);
            env1.setRelease(parameters->release);
    
    filter_envelope.setAttack(parameters->attack);
    filter_envelope.setDecay(parameters->decay);
    filter_envelope.setSustain(parameters->sustain);
    filter_envelope.setRelease(parameters->release);
    
            for (int sample = 0; sample < numSamples; ++sample)
            {
                
              // GENERATE SIGNALS
                
                // DETUNE PROCESSING
                
                float osc_1_detune_amount = 1 + (parameters->osc_1_detune / 1000);
                float osc_2_detune_amount = 1 + (parameters->osc_2_detune / 1000);
                
                
                double osc_signal = hw_osc_1.do_Oscillate(osc_1_frequency * osc_1_detune_amount, parameters->osc_1_wave); // add cents to pitch
                double osc2_signal = hw_osc_2.do_Oscillate(osc_2_frequency * osc_2_detune_amount, parameters->osc_2_wave);
                double oscNoise_signal = hw_osc_noise.do_Oscillate(frequency, 5);
                
                
                // MIXER SECTION
                    // ADJUST LEVELS
                osc_signal *= parameters->osc1_volume;
                osc2_signal *= parameters->osc2_volume;
                oscNoise_signal *= parameters->osc_noise_volume;
                    // AND SUM TOGETHER
                double oscMixed = (osc_signal + osc2_signal + oscNoise_signal) * 0.33;
                
                
            // APPLY VOLUME ENVELOPE TO THE SIGNALS
                double oscEnv = env1.adsr(oscMixed, env1.trigger) * level;
            // RUN IT THROUGH A FILTER
                
                
                // Cutoff knob value from gui
                float filter_cutoff_target = parameters->filter_cutoff;
    
                
                // runs knob value through an envelope ramp
                float filter_env = (filter_cutoff_target / 4 ) + (filter_envelope.adsr(filter_cutoff_target, env1.trigger) * parameters->filter_envelope_amount);
                
                if (filter_env >= 18000)
                {
                    filter_env = 18000;
                }
                
                if (filter_env <= 50)
                {
                    filter_env = 50;
                }
                
                double oscFilt = hw_filter.process_sample(oscEnv, filter_env, parameters->filter_resonance, parameters->filter_type);
                
                double outputSample = oscFilt;
                
                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {
                    outputBuffer.addSample(channel, startSample, outputSample);
                }
                
                ++startSample;
            }
}



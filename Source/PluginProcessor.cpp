

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthTakeIiAudioProcessor::SynthTakeIiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    
    apvts.state.addListener(this);
    
    hw_Synth.clearVoices();
    
    for (int i = 0; i < 4; ++i)
    {
        hw_Synth.addVoice(new SynthVoice(&params));
    }
    
    hw_Synth.clearSounds();
    
    hw_Synth.addSound(new SynthSound());
    
    
    
}

SynthTakeIiAudioProcessor::~SynthTakeIiAudioProcessor()
{
}

//==============================================================================
const String SynthTakeIiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthTakeIiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthTakeIiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthTakeIiAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthTakeIiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthTakeIiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthTakeIiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthTakeIiAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthTakeIiAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthTakeIiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthTakeIiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    hw_Synth.setCurrentPlaybackSampleRate(lastSampleRate);
    delay.setFs(sampleRate);
}

void SynthTakeIiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthTakeIiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthTakeIiAudioProcessor::debugParams() {
    DBG("Attack: " << *apvts.getRawParameterValue("ATTACK"));
    DBG("Decay: " << *apvts.getRawParameterValue("DECAY"));
    DBG("Sustain: " << *apvts.getRawParameterValue("SUSTAIN"));
    DBG("Release: " << *apvts.getRawParameterValue("RELEASE"));
    //LFO
    DBG("Rate: " << *apvts.getRawParameterValue("RATE"));
    DBG("Depth: " << *apvts.getRawParameterValue("DEPTH"));
    DBG("LFO WAVE: " << *apvts.getRawParameterValue("LFO_WAVE"));
    // OSC 1
    DBG("Osc 1 TYPE: " << *apvts.getRawParameterValue("OSC1_WAVE"));
    DBG("Osc 1 Pitch Semitones: " << *apvts.getRawParameterValue("OSC1_PITCH"));
    DBG("Osc 1 Detune Cents: " << * apvts.getRawParameterValue("OSC1_DETUNE"));
    // OSCsc
    DBG("Osc 2 TYPE: " << *apvts.getRawParameterValue("OSC2_WAVE"));
    DBG("Osc 2 Pitch Semitones: " << *apvts.getRawParameterValue("OSC2_PITCH"));
    DBG("Osc 2 Detune Cents: " << * apvts.getRawParameterValue("OSC2_DETUNE"));
    // FILTER
    DBG("Filter Type: " << *apvts.getRawParameterValue("FILTER_TYPE"));
    DBG("Filter Cutoff: " << *apvts.getRawParameterValue("FILTER_CUTOFF"));
    DBG("Filter Resonance: " << *apvts.getRawParameterValue("FILTER_RESONANCE"));
    // FX
    DBG("DIST: " << *apvts.getRawParameterValue("DISTORTION"));
    // OUTPUT
    DBG("PAN: " << *apvts.getRawParameterValue("PAN"));
    DBG("OP: " << *apvts.getRawParameterValue("OUTPUT"));
}

void SynthTakeIiAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    // Clear any leftovers in the buffer
    buffer.clear();

    // update parameters in the synth voice
   // if (mustUpdateProcessing)
        update();
    
    // generate the next synth block
    hw_Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    // Get params for on a block-by-block basis
    float distortion_wetdry_balance = *apvts.getRawParameterValue("DISTORTION_WETDRY");
    float delay_wetdry_balance = *apvts.getRawParameterValue("DELAY_WETDRY");
    
    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
         
            float x = buffer.getWritePointer(channel)[i];
            
            // Process Waveshaper
            float input_to_distortion = x;
            float output_of_distortion = hw_Distortion.processSample(input_to_distortion, *apvts.getRawParameterValue("DISTORTION"), *apvts.getRawParameterValue("DISTORTION_TYPE"));
            
                // DISTORTION WET DRY BLEND
            
            x = ((1.0 - distortion_wetdry_balance) * x) + (distortion_wetdry_balance * output_of_distortion);
            
            // Process Delay
            delay.setSpeed(*apvts.getRawParameterValue("DELAY_MODULATION"));
            delay.setDelaySamples(*apvts.getRawParameterValue("DELAY_TIME") * 44.1);
            
            // the input to delay is the regular signal, plus the output is fed back into the line
            float input_to_delay = x + (-*apvts.getRawParameterValue("DELAY_FEEDBACK")
                                        * delayFeedbackSample[channel]);
            
            float output_of_delay = delay.processSample(input_to_delay, channel, *apvts.getRawParameterValue("DELAY_GROOVE"));
            
            // Set feedback sample
            delayFeedbackSample[channel] = delay_repeats_distortion.processSample(output_of_delay, 0.9, 3);
                // DELAY WET DRY BLEND
            
            x = ((1.0 - delay_wetdry_balance) * x) + (delay_wetdry_balance * output_of_delay);
            
            
            // Process Gain - INCLUDE PAN HERE
            x *= * apvts.getRawParameterValue("OUTPUT");
        
            // Write to buffer
            float y = x; // Set output samples
            buffer.getWritePointer(channel)[i] = y;
        }
    }
}

//==============================================================================
bool SynthTakeIiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthTakeIiAudioProcessor::createEditor()
{
    return new SynthTakeIiAudioProcessorEditor (*this);
}

//==============================================================================
void SynthTakeIiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthTakeIiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

/*
 
 This is a key method for connecting the GUI to the voice processing
 in SynthVoice.h
 
 We pass values to the SynthVoiceParams struct which is serves as a bridge between the apvts
 and the SynthVoice file 
 
 
 */
void SynthTakeIiAudioProcessor::update()
{
    mustUpdateProcessing = false;
    
    
    // ADSR
    params.attack = apvts.getRawParameterValue("ATTACK")->load(); // IMPLEMENTED
    params.decay = apvts.getRawParameterValue("DECAY")->load();  // IMPLENENTED
    params.sustain = apvts.getRawParameterValue("SUSTAIN")->load(); // IMPLEMENTED
    params.release = apvts.getRawParameterValue("RELEASE")->load(); // IMPLEMENTED
    // OSC 1
    params.osc_1_wave = apvts.getRawParameterValue("OSC1_WAVE")->load(); // IMPLEMENTED
    params.osc_1_pitch = apvts.getRawParameterValue("OSC1_PITCH")->load(); // IMPLEMENTED
    params.osc_1_detune = apvts.getRawParameterValue("OSC1_DETUNE")->load(); // MORE RESEARCH REQUIRED
    // OSC 2
    params.osc_2_wave = apvts.getRawParameterValue("OSC2_WAVE")->load(); // IMPLEMENTED
    params.osc_2_pitch = apvts.getRawParameterValue("OSC2_PITCH")->load(); // IMPLEMENTED
    params.osc_2_detune = apvts.getRawParameterValue("OSC2_DETUNE")->load(); // MORE RESEARCH REQUIRED
    
    // FILTER SECTION
    
    params.filter_type = apvts.getRawParameterValue("FILTER_TYPE")->load(); // IMPLEMENTED
    params.filter_cutoff = apvts.getRawParameterValue("FILTER_CUTOFF")->load(); // IMPLEMENTED
    params.filter_resonance = apvts.getRawParameterValue("FILTER_RESONANCE")->load(); // IMPLEMENTED
    params.filter_envelope_amount = apvts.getRawParameterValue("FILTER_EG_AMOUNT")->load(); // NOT IMPLEMENTED
    
    // MIXER SECTION
        
    params.osc1_volume = apvts.getRawParameterValue("OSC1_VOLUME")->load(); // IMPLEMENTED
    params.osc2_volume = apvts.getRawParameterValue("OSC2_VOLUME")->load(); // IMPLEMENTED
    params.osc_noise_volume = apvts.getRawParameterValue("OSCNOISE_VOLUME")->load(); // IMPLEMENTED 
    
}





//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthTakeIiAudioProcessor();
}

// Returns a ParameterLayout object from the AudioProcessorValueTreeState class

AudioProcessorValueTreeState::ParameterLayout
SynthTakeIiAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
    
    // OSC 1 PARAMS
    parameters.push_back(std::make_unique<AudioParameterInt>("OSC1_WAVE", "Osc1_Wave", limits.osc_wave_min, limits.osc_wave_max, limits.osc_wave_default));
    parameters.push_back(std::make_unique<AudioParameterInt>("OSC1_PITCH", "Osc1_Pitch", limits.osc_pitch_min, limits.osc_pitch_max, limits.osc_pitch_default));
    parameters.push_back(std::make_unique<AudioParameterFloat>("OSC1_DETUNE", "Osc1_Detune", limits.osc_detune_min, limits.osc_detune_max, limits.osc_detune_default));
    
    // OSC 2 PARAMS
    parameters.push_back(std::make_unique<AudioParameterInt>("OSC2_WAVE", "Osc2_Wave", limits.osc_wave_min, limits.osc_wave_max, limits.osc_wave_default));
    parameters.push_back(std::make_unique<AudioParameterInt>("OSC2_PITCH", "Osc2_Pitch", limits.osc_pitch_min, limits.osc_pitch_max, limits.osc_pitch_default));
    parameters.push_back(std::make_unique<AudioParameterFloat>("OSC2_DETUNE", "Osc2_Detune", limits.osc_detune_min, limits.osc_detune_max, limits.osc_detune_default));
    
    // FILTER PAR
    parameters.push_back(std::make_unique<AudioParameterInt>("FILTER_TYPE", "Filter_Type", limits.filter_type_min, limits.filter_type_max, limits.filter_type_default));
    parameters.push_back(std::make_unique<AudioParameterFloat>("FILTER_CUTOFF", "Filter_Cutoff", limits.filter_cutoff_min, limits.filter_cutoff_max, limits.filter_cutoff_default));
    parameters.push_back(std::make_unique<AudioParameterFloat>("FILTER_RESONANCE", "Filter_Resonance", limits.filter_resonance_min, limits.filter_resonance_max, 0.01));
    parameters.push_back(std::make_unique<AudioParameterFloat>("FILTER_EG_AMOUNT", "Filter_Envelope_Amount", 0.2f, 1.5f, 1));
    
    // ADSR
    parameters.push_back(std:: make_unique<AudioParameterFloat>("ATTACK", "Attack", limits.attack_min, limits.attack_max, limits.attack_default));
    parameters.push_back(std:: make_unique<AudioParameterFloat>("DECAY", "Decay", limits.decay_min, limits.decay_max, limits.decay_default));
    parameters.push_back(std:: make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", limits.sustain_min,limits.sustain_max ,limits.sustain_default ));
    parameters.push_back(std:: make_unique<AudioParameterFloat>("RELEASE", "Release", limits.release_min, limits.release_max, limits.release_default));
    
    // LFO
    parameters.push_back(std::make_unique<AudioParameterFloat>("RATE", "Rate", limits.lfo_min,limits.lfo_max ,limits.lfo_default ));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DEPTH", "Depth", limits.lfo_depth_min, limits.lfo_depth_max, limits.lfo_depth_default));
    parameters.push_back(std::make_unique<AudioParameterInt>("LFO_WAVE", "Wave", limits.lfo_wave_min, limits.lfo_wave_max, limits.lfo_wave_default));
    
    // FX SECTION
        // DISTORTION PARAMS
    parameters.push_back(std::make_unique<AudioParameterFloat>("DISTORTION", "Distortion", 0.001, 5.0f, 1.f));
    parameters.push_back(std::make_unique<AudioParameterInt>("DISTORTION_TYPE", "Distortion_Type", 1,4,1));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DISTORTION_WETDRY", "Distortion Blend", 0.0f, 1.0f, 0.5f));
    
    
    
        // Delay PARAMS
    parameters.push_back(std::make_unique<AudioParameterFloat>("DELAY_TIME", "Delay Time", 0, 1750, 250));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DELAY_FEEDBACK", "Delay Feedback", 0.0f, 2.f, 0.5f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DELAY_MODULATION", "Modulation", 0.01, 15.f, 2.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DELAY_GROOVE", "Delay Groove", 1.f, 2, 1.01));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DELAY_WETDRY", "Delay Blend", 0.0f, 1.0f, 0.5f));
    
    // OUTPUT SECTION
    
        // MIXER
    
    
    parameters.push_back(std::make_unique<AudioParameterFloat>("OSC1_VOLUME", "Osc_I", 0.0, 1.0f, 1.f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("OSC2_VOLUME", "Osc_II", 0.0, 1.0f, 1.f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("OSCNOISE_VOLUME", "Osc_Noise", 0.0, 1.0f, 0.05f));
    
    parameters.push_back(std::make_unique<AudioParameterFloat>("OUTPUT", "Output", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("PAN", "Pan", -50.f, 50.f, 0.f));
    
    return { parameters.begin(), parameters.end() };
}

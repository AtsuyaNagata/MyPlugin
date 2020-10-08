/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyPluginAudioProcessor::MyPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MyPluginAudioProcessor::~MyPluginAudioProcessor()
{
}

//==============================================================================
const String MyPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String MyPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MyPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MyPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MyPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    //“ü—Íƒ`ƒƒƒ“ƒlƒ‹”‚ÌŠl“¾
    auto totalNumInputChannels = getTotalNumInputChannels();
    //o—Íƒ`ƒƒƒ“ƒlƒ‹”‚ÌŠl“¾
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //Žg—p‚µ‚È‚¢ƒ`ƒƒƒ“ƒlƒ‹‚Ìƒoƒbƒtƒ@‚ðƒNƒŠƒA‚·‚éˆ—iŽg—p‚µ‚È‚¢ƒ`ƒƒƒ“ƒlƒ‹‚ÍInput‚æ‚è‚à‚Í‚Ýo‚½•ª‚ÌOutputj
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float level = 0.5f;     //‰¹—Ê‚ÌƒŒƒxƒ‹‚ð—\‚ß‰º‚°‚Ä‚¨‚­Ž–‚ð‘z’è‚µ‚Ä”{—¦‚ðÝ’è‚µ‚Ä‚¨‚­

    //“ü—Íƒ`ƒƒƒ“ƒlƒ‹‚Ì”‚¾‚¯M†ˆ—‚ðŒJ‚è•Ô‚·B¡‰ñ‚Í“Á‚É‰½‚à‚µ‚È‚¢
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        float* channelData = buffer.getWritePointer(channel);       //Žw’è‚µ‚½ƒ`ƒƒƒ“ƒlƒ‹‚Ìƒoƒbƒtƒ@‚Ìæ“ª‚ÌŽQÆ‚ð‚à‚ç‚Á‚Ä‚é
    }

    //o—Íƒ`ƒƒƒ“ƒlƒ‹‚Ì”‚¾‚¯M†ˆ—‚ðŒJ‚è•Ô‚·
    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        //‘Î‰ž‚·‚éƒ`ƒƒƒ“ƒlƒ‹‚Ì1ƒ`ƒƒƒ“ƒlƒ‹•ª‚Ìƒoƒbƒtƒ@‚Ìæ“ªƒAƒhƒŒƒX‚ÌŠl“¾
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            //Å‘åƒTƒ“ƒvƒ‹‚ÅˆêŽü‚·‚é—l‚ÉŠp“x‚ðŒvŽZ
            const float currentAngle = juce::MathConstants<float>::pi * 2.0f * sample / buffer.getNumSamples();
            //sin”g‚ÌŠÖ”‚ÉŒvŽZ‚µ‚½Šp“x‚ð“ü‚ê‚ÄA•Ô‚è’l‚ðfloat”z—ñ‚ÉŠi”[‚·‚é
            channelData[sample] = sinf(currentAngle) * level;
        }
    }
}

//==============================================================================
bool MyPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MyPluginAudioProcessor::createEditor()
{
    return new MyPluginAudioProcessorEditor (*this);
}

//==============================================================================
void MyPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyPluginAudioProcessor();
}

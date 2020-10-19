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


//MyMemberProcess
void MyPluginAudioProcessor::setupSampler(AudioFormatReader& newReader)
{
    isChanging = true;      //skip flag in processBlock()
    
    //delete synth object
    synth.clearSounds();
    synth.clearVoices();

    BigInteger allNotes;
    allNotes.setRange(0, 128, true);     //assign Note "true" (Range : 0 - 127)

    synth.addSound(new SamplerSound("default", newReader, allNotes, 60, 0, 0.1, 10));

    //add SamplerVoice Object 128 times for play 128 Sounds in same time
    for (int i = 0; i < 128; ++i) {
        synth.addVoice(new SamplerVoice());
    }

    isChanging = false;
}

void MyPluginAudioProcessor::loadSineWave()
{
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    //create MemoryInputStream instance from sine_wave BinaryData
    MemoryInputStream* inputStream = new MemoryInputStream(BinaryData::sine_wav, BinaryData::sine_wavSize, true);
    //create AudioFormatReader instance
    AudioFormatReader* reader = formatManager.createReaderFor(inputStream);

    if (reader != nullptr)
    {
        setupSampler(*reader);
        delete reader;
    }
}

void MyPluginAudioProcessor::loadSampleFile()
{
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    FileChooser chooser("Open audio file to play", File(), formatManager.getWildcardForAllFormats());

    if (chooser.browseForFileToOpen())
    {
        File file(chooser.getResult());
        AudioFormatReader* reader = formatManager.createReaderFor(file);

        if (reader != nullptr)
        {
            setupSampler(*reader);
            delete reader;
        }
    }
}

//This process is executed when initialize
void MyPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);     //set SampleRate on Synth
    keyboardState.reset();      //initialize Midikeyboard Object
}

//This process is executed when delete
void  MyPluginAudioProcessor::releaseResources()
{
    keyboardState.allNotesOff(0);           //set 0 to set NoteOff all channel
    keyboardState.reset();
}

void  MyPluginAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (isChanging) { return; }

    ScopedNoDenormals noDenormals;
    int totalNumInputChannel = getTotalNumInputChannels();
    int totalNumOutChannels = getTotalNumOutputChannels();

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    for (auto i = totalNumInputChannel; i < totalNumOutChannels; ++i)
    {
        buffer.clear();
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}
/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class MyPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MyPluginAudioProcessor();
    ~MyPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //‚±‚±‚ÉAudio‚âMIDI‚Ìƒf[ƒ^‚ð‰ÁH‚·‚éˆ—‚ð‘‚­BƒGƒtƒFƒNƒg‚Ìê‡‚ÍAudioƒf[ƒ^AƒCƒ“ƒXƒgƒDƒ‹ƒƒ“ƒg‚ÍMIDIƒf[ƒ^‚ðŽó‚¯Žæ‚é
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    //=======MyMember=======
    void setupSampler(AudioFormatReader& newReader);    //load Sample Sound and init SamplerVoice Object
    void loadSineWave();        //load Sine Wave from Binary Resource
    void loadSampleFile();      //load Sample Sound from File Browser
    MidiKeyboardState& getMidiKeybordState() { return keyboardState; }



private:
    Synthesiser synth;
    MidiKeyboardState keyboardState;
    bool isChanging;        //flag to decide to Skip process in processBlock

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyPluginAudioProcessor)

};

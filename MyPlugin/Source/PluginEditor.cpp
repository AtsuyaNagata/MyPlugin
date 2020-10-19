/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyPluginAudioProcessorEditor::MyPluginAudioProcessorEditor (MyPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), keyboardComponent(p.getMidiKeybordState(), MidiKeyboardComponent::horizontalKeyboard)
{
    sineWaveButton.setButtonText("Sine Wave");
    sineWaveButton.addListener(this);
    sampleSelectButton.setButtonText("Sample Select");
    sampleSelectButton.addListener(this);
    
    addAndMakeVisible(sineWaveButton);
    addAndMakeVisible(sampleSelectButton);
    addAndMakeVisible(keyboardComponent);

    setSize(800, 600);
}

MyPluginAudioProcessorEditor::~MyPluginAudioProcessorEditor()
{
}

//==============================================================================
void MyPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MyPluginAudioProcessorEditor::resized()
{
    sineWaveButton.setBoundsRelative(0.2, 0.2, 0.2, 0.2);
    sampleSelectButton.setBoundsRelative(0.6, 0.2, 0.2, 0.2);
    keyboardComponent.setBoundsRelative(0.0, 0.7, 1.0, 0.3);
}

void MyPluginAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &sineWaveButton) {
        processor.loadSineWave();
    }
    else if (button == &sampleSelectButton) {
        processor.loadSampleFile();
    }
}
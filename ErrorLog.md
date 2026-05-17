# myFXPlayer Error Log

---

## juce::AudioBuffer<float>& buffer

> Every audio component shares one buffer(noitice the &) when "void process" in according files.

In PluginProcessor.cpp processBlock(), noise is the first audio component who process(buffer), so we can write "data[] = " in Noise.h process(). Waveform and others which below noise should write "data[] += " in according files process().

---

## Ramp and Loops

Nested order of double loops:  

### 1. channel-wise

```C++
for(channel){
    
    auto* data = buffer.getWritePointer(channel);
    
    for(sample){
        float currentGain = smoothedGain.getNextValue();
        // ...
    }
}
```

Execution process analysis:  

> 1. Enter channel 0 (left channel)  
>    - sample = 0, getNextValue() = 0.1  
>    - sample = 1, getNextValue() = 0.2  
>    - ...  
>    - sample = 3, getNextValue() = 0.4  
>    - Left channel finished.  
> 2. Enter channel 1 (right channel)
>    - sample = 0, getNextValue() = **0.5**
>    - sample = 1, getNextValue() = **0.6**
>    - ...

We can hear gain ramp in left channel, but the right channel is begin with 0.5  
This sound may **left-right imbalance**

### 2. sample-wise

```C++
for(sample) {
    
    const float currentGain = smoothedGain.getNextValue();
  
    for (channel) {
        auto* data = buffer.getWritePointer(channel);
        // ...
    }
}
```

Execution process analysis:

> 1. sample = 0, getNextValue() = 0.1
>   - left = 0.1, right = 0.1
> 2. sample = 1, getNextValue() = 0.2  
>   -left = 0.2, right = 0.2
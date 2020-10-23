# 300 - Down the rabbit hole (Solution)

## Finding the challenge

The challenge is a section of the twitch stream being looped on twitch.tv/over_the_air. It occurs very quickly during the Ovaltine commercial at about 14:20 into the video. There should be a quick scene of a woman wearing a face mask w/ hex scrolling across it and some audio tones playing over it.


## Capturing the challenge

We've turned clips off for the channel. You have two ways to capture the challenge:

1. youtube-dl the twitch stream while the challenge is playing
2. Record the audio using some other mechanism and screenshot or write down the hex value

## Solving the challenge

Once you've captured the challenge, you'll have an audio clip of some tones. Those tones are DTMF tones, or what most people think of as the sounds that occur when you dial a phone. You can determine the actual numbers based on their frequencies. Either import the audio into something like Audacity and take a look at the spectrogram. Using the chart [here](https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling#Keypad) you can figure out which numbers were pressed. If you don't want to do it manually, there are automated methods where you can upload the audio like [this one](http://dialabc.com/sound/detect/). 

Either way, you should end up with this: `5038326682`

It's the right length for a phone number, so give it a call. If you do, you should reach an automated system welcoming you to the BSidesPDX secret message sharing service. The only issue is, in order to retrieve a message, you need a 5 digit code. Think back to the video that was associated with the DTMF tones. There was a hex value there. Converting the hex value (0x13A5C) to decimal gets you 80476. Input this number and you get a secret message.

Of course, it's just more audio tones, because of course it is. 

This should be easily recognizable as Morse code. You can either quickly write down the dots and dashes by hand, or record the audio and use an automated decoder like [this one](https://morsecode.world/international/decoder/audio-decoder-adaptive.html) (if you use this one, you may need to clear the message and replay it once it figures out the correct WPM). Either way, once decoded you should have the message `MSG NUM 41683`.

Another 5 digit number, maybe this is another secret message code? Calling the BSidesPDX secret message sharing service again and putting in that number gets you a different message, this time just saying to visit the URL `overtheair.space`. 

Visiting that site directs you to a couple minute long [YouTube video](https://www.youtube.com/watch?v=YcArof3MXx8). It seems pretty normal until just after the 1 minute mark where, yet again, we start to hear some strange tones. What is it with the challenge authors and freaking audio?!

This one will likely be more difficult to identify if you've never seen it before. It's an [SSTV signal](https://en.wikipedia.org/wiki/Slow-scan_television). This time, there's no manual decoding. You'll have to grab the audio/download the video/something and use an SSTV decoder. I used qsstv on Linux, but there are a number of possible decoders out there. Most will not just let you open an audio file and decode it and instead only take audio from a microphone input. You may have to setup an audio loopback from the output. [This guide](https://wiki.debian.org/audio-loopback) works well if you're on a Debain/Ubuntu system, but if you're not then you'll have to figure that one out on your own.

Either way, once you can get to the point of decoding the SSTV signal, you should have a single image which has the flag in it. Finally. And if you don't understand the reference in the flag, [watch this](https://www.youtube.com/watch?v=zdA__2tKoIU). Welcome to the secret circle.

## Flag

```
BSidesPDX{b3_sUR3_T0_dr!nk_y0Ur_Ov4ltin3}
```

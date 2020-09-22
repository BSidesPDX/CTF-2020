# 200 - Xclusive Numborz (Solution)

## Finding the challenge

The challenge is a section of the twitch stream being looped on twitch.tv/over_the_air. It is signaled by a short rendition of Bella Ciao (played by yours truly), and the image found in the src repository.


## Capturing the challenge

This challenge is too long to reasonably capture in one twitch clip, plus we've turned clips off for the channel. You have two ways to capture the challenge:

1. youtube-dl the twitch stream while the challenge is playing
2. Write the hexadecimal digits fast and furiously and hope you don't mess up

## Solving the challenge

Once you've captured the challenge, you'll have a couple audio clips of my niece saying creepy things, plus a long string of hexadecimal digits. The first creepy thing is just a distraction, but the last creepy thing (are you my mommy) is a signal for your xor key, and it is emphasized by being duplicated, pitch bent, and delayed.


The hexadecimal string you should have: `23210c1d0a063d3d351419054a3e1c10140d461f0a321c1d5e4d0a2d51261b1d5e141e5c011b4a12`


Once you have this string, you might try to decode it and say 'wait a minute what is this' and then you'll have to think back to the hints we've given in the challenge text.


By xoring the hexadecimal string with "areyoumymommy", you'll get the flag. You can start to get an idea for the formatting of the xor key because you know that all flags begin with `BSidesPDX{` and they end with `}`

## Flag

```
BSidesPDX{th3_numb3rs_sp34k_4_th3ms3lv3s}
```

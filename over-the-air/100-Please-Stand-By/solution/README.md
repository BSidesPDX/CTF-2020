# 100 - Please Stand By (Solution)

## Finding the challenge

This challenge happens in between airings of the TV show on twitch.tv/over_the_air. If you see the Please Stand By test pattern, you're in the right place.


## Capturing the challenge

This challenge only really needs a screenshot mechanism. You'll need to screenshot each of the QR code test patterns.

## Solving the challenge

Once you've taken a screenshot of each QR code test pattern (there are 4, one in each corner in a clockwise pattern), you need to reassemble the QR code. But wait! They aren't in the right corners, so you'll have to figure out the correct orientation. This shouldn't be too hard if you've ever seen a QR code, but basically the corners are swapped - top left <-> bottom right, bottom left <-> top right. 

There is some tolerance for imperfection in the QR code algorithm, however you'll want to make sure to not leave gaps too big, and make sure it's all lined up correctly etc.

The final step is to read through the zalgo text in order to see the underlying flag. The zalgo text isn't the flag itself (you can't just paste the zalgo text into the scoreboard), but if you read it you'll be able to see the flag. There's also the [zalgo remover](https://cable.ayra.ch/zalgo/) site which can be used to remove the zalgo text and retrieve the flag.

## Flag

```
BSidesPDX{5tAnd_bY_f0r_An_!mp0rtan7_Me55aGe}
```

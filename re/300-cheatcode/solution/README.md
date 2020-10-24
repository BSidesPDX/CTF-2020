# RE300 - cheatcode - Solution

## High-Level Steps

For the time-being, this writeup will be pretty brief and hand-wavy, but I wanted to at least provide an outline for the highlevel steps to solving this weird challenge.  I will do my best to come back to it and add more details.  When creating this challenge, I didn't expect people in the Portland community to already be familiar with Nintendo Switch homebrew.  The hope was that for the most determined teams, they would be able to perform enough googling, research, cruising source code, and understanding homebrew toolchains to solve this.


### What is an `.nro` file?

You may have noticed that running the `file` command on this binary doesn't provide any useful information.

Well, if you google `nro file`, the very first result shows the following:

> An NRO file is an executable file used by the Nintendo Switch video game console or Switch emulator, such as Yuzu or Ryujinx. It contains compiled code for an ...

This follows with the theme of the name of the challenge, `cheatcode`.


### How to decompile an `.nro` file?

If you Google for `nro ghidra`, the first two results reference the Github repo: [Ghidra-Switch-Loader](https://github.com/Adubbz/Ghidra-Switch-Loader).  You can use this to make loading the binary into Ghidra much easier.


### How to run an `.nro` file, I don't have a hacked Switch!

If you Google for `nintendo switch emulator`, the first result was for the [yuzu emulator](https://yuzu-emu.org/).  When creating this challenge, this is what I used to test against.  Documentation and the tool itself will suggest that it needs to use actual Switch Encryption keys to run games, but this is only true for official, licensed games for the Nintendo Switch.  It can execute homebrew applications without any additional keys!


### I can run the homebrew and I've got it decompiled, now what?

Since you've ran the homebrew application, you have already been presented with a black screen, white text that says: `Enter the secret cheat code to reveal the flag.`.

So now the objective is a little more clear, we have to figure out the hidden sequence of button presses to trigger decryption of the flag.

The way I was anticipating people would reason through this, is to ask themselves the questions:
- If I were the one creating this challenge, how would I do it?
- How does Switch homebrew work?
- Are there any simpler examples of Switch homebrew that I could try and compile then decompile to get a better handle of things?

If you google for `switch examples homebrew`, the first result is a Github Repo, [switchbrew/switch-examples](https://github.com/switchbrew/switch-examples) and the second result is to the [Switchbrew Development Environment Setup page](https://switchbrew.org/wiki/Setting_up_Development_Environment).

So now you have everything needed to compile your own Switch homebrew applications.  Now, for which example to focus on?  Since we're mostly interested in how controlls are handled, let's find an example doing exactly that!

The [hid/read-controls](https://github.com/switchbrew/switch-examples/tree/master/hid/read-controls) example would probably be a good place to start.  In fact, when creating this challenge, I started with this as the base!

For starters, notice that there is a note at the top of the example source: `//See also libnx hid.h.`.  Additionally we have these key control names:

```
    //Matrix containing the name of each key. Useful for printing when a key is pressed
    char keysNames[32][32] = {
        "KEY_A", "KEY_B", "KEY_X", "KEY_Y",
        "KEY_LSTICK", "KEY_RSTICK", "KEY_L", "KEY_R",
        "KEY_ZL", "KEY_ZR", "KEY_PLUS", "KEY_MINUS",
        "KEY_DLEFT", "KEY_DUP", "KEY_DRIGHT", "KEY_DDOWN",
        "KEY_LSTICK_LEFT", "KEY_LSTICK_UP", "KEY_LSTICK_RIGHT", "KEY_LSTICK_DOWN",
        "KEY_RSTICK_LEFT", "KEY_RSTICK_UP", "KEY_RSTICK_RIGHT", "KEY_RSTICK_DOWN",
        "KEY_SL_LEFT", "KEY_SR_LEFT", "KEY_SL_RIGHT", "KEY_SR_RIGHT",
        "KEY_TOUCH", "", "", ""
    };
```

Let's take a look at the libnx [hid.h](https://github.com/switchbrew/libnx/blob/master/nx/include/switch/services/hid.h#L247) header.

So these are the hardcoded values of each controller input button.  So next you will have to return to Ghidra and see if you can find values like these in the binary anywhere, perhaps stored in array.

Hopefully after staring at both the assembly and decompiler output, you'll eventually realize that the cheat code array is stored here: `0x710002c0f8`.  So you can use the `hid.h` header to figure out which key corresponds to each value in that array.  Once you have the cheat code sequence derived (`KEY_DDOWN, KEY_DUP, KEY_DUP, KEY_DLEFT, KEY_DLEFT, KEY_A, KEY_A, KEY_DRIGHT, KEY_B, KEY_DDOWN, KEY_DLEFT`), simply enter it into your emulator!

It should print some BSidesPDX Sasquatch ascii art followed by the decoded flag: `BSidesPDX{c0ns0l3s_ar3_jU57_c0MPU73rS_th3Y_d0Nt_wAnT_YOU_2_wr1t3_c0d3_f0r!}`.

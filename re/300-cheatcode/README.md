# 300 - cheatcode

## Description

Provided is an nro file, which is commonly how Nintendo Switch homebrew applications are distributed.  The application was built using libnx, specifically derived from the [hid/read-controls sample code](https://github.com/switchbrew/switch-examples/blob/master/hid/read-controls/source/main.c).  The application is looking for a hard-coded sequence of button presses.  If these are received, the flag is decrypted and printed to the screen.  The application can be run on either a vulnerable Nintendo Switch running custom firmware or on the [Yuzu Emulator](https://yuzu-emu.org/).  Additionally, there are plugins for both Ghidra and IDA Pro that can allow you to disassemble and analyze NRO binaries.

## Deploy

Follow these instructions for setting up a [Nintendo Switch homebrew development environment](https://switchbrew.org/wiki/Setting_up_Development_Environment).  Then simply run `make` in the `src/` folder.

## Challenge

Try and find the secret cheat code to reveal the flag!

Author(s): aagallag

Flag: `BSidesPDX{c0ns0l3s_ar3_jU57_c0MPU73rS_th3Y_d0Nt_wAnT_YOU_2_wr1t3_c0d3_f0r!}`

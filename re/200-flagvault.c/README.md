# 200 - flagvault.c

## Description

Players are provided with an x86-64 binary, `flagvault` that can encrypt and decrypt files.  This challenge includes the same issue as the Android Flag Vault challenge, in that the password is checked in software before decrypting the flag.  So the player must reverse engineer the `verify_password` function to derive the password used to encrypt the file.  To make the challenge a little bit harder, the `verify_password` function is encoded with an XOR and is un-encoded at run-time.

## Deploy

Run `make` in the `src/` folder.  Then encrypt your flag file with `./flagvault -e -p <flagfile> -c <flagfile.enc>`.  Be sure to use the hardcoded password, `n0b0dy_g3tz_h4ck3d!`.

## Challenge

Ok, I learned my lesson.  Java was a bad idea, so this time I wrote it in C and used state-of-the-art obfuscation!  Can you decrypt flag.png.enc?

Author(s): aagallag

Flag: `BSidesPDX{m3_wh3n_i_h4v3_an_IQ_of_197_&_100%_0f_y0ur_p4ssw0rD}`

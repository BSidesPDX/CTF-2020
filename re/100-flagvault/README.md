# 100 - Flag Vault

## Description

Provided is an APK for a simple Android application.  It takes a password as input, performs validation on the password.  If validation passes, then the password is used to decrypt the AES cipher text containing the flag.  The APK can be decompiled and the password validation routine (`VaultManager.CheckPassword(String s)`) can be reversed to derive the password.

## Deploy

Compile with Android Studio and provide the APK via the scoreboard.

## Challenge

Can you break into the flag vault?

Author(s): aagallag

Flag: `BSidesPDX{g00d_crypt0_1s_h4rd_70_d0!>>}`

# RE100 - Flag Vault - Solution

## Working with APK's

Since we are provided with an APK, you can do some googling to discover that an APK is how Android applications are distributed.  From experience, I generally avoid using `apktool` since that generates smali bytecode.  This is great if you plan on making modifications to the application, as you can use apktool to rebuild the apk with the modified smali bytecode, but smali bytecode is a pain to read.

Instead, I prefer to start with using tools to extract approximate java source code from the APK.  There's a bunch of ways to accomplish this, below are a few of them:

- You can use apktool to get the jar, and then use [jd-gui](https://java-decompiler.github.io/) to decompile to java source.
- You can use [jadx](https://github.com/skylot/jadx) to go straight from apk to Java source.
- You can use [MobSF](https://github.com/MobSF/Mobile-Security-Framework-MobSF) to decompile to java source (as well as retrieve additional information about the app).
- Or easiest yet, there are a couple online decompilers where you simply upload an APK, and it allows you to download a zip containing the Java source code.  Example: [apkdecompilers.com](https://www.apkdecompilers.com/)

I went with the last option because it's quick, easy, and doesn't require installing any tools.

So once you have the source code, you'll have to poke around for the code, relevant to the challenge.  It's good to look for folder names that are familiar, perhaps containing the name of the CTF or the challenge.  Specifically, we are looking for `MainActivity.java` as this is the entry point for most Android applications.

For this challenge, this can be found in the folder: `com\bsidespdx\flagvault\`.

## Reversing the Java code

Under `com\bsidespdx\flagvault\` we have the following files:

```
AES.java
BuildConfig.java
MainActivity.java
R.java
VaultManager.java
```

Let's start with `MainActivity.java`, because as mentioned before, this is likely to be the entry point for the Application (you can think of it as the equivelant to Android's `main()` function).

```java
package com.bsidespdx.flagvault;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    /* access modifiers changed from: protected */
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView((int) R.layout.activity_main);
    }

    public void onDecrypt(View view) {
        TextView textView = (TextView) findViewById(R.id.vaultResult);
        String obj = ((EditText) findViewById(R.id.vaultPasswordEntry)).getText().toString();
        textView.setText(VaultManager.CheckPassword(obj) ? VaultManager.DecryptFlag(obj) : "Invalid vault password provided");
    }
}

```

So the most interesting code is the last line of `onDecrypt`.

```java
textView.setText(VaultManager.CheckPassword(obj) ? VaultManager.DecryptFlag(obj) : "Invalid vault password provided");
```

This is basically calling `VaultManager.CheckPassword(obj)`, if it returns true, then it passes `obj` onto `VaultManager.DecryptFlag(obj)`.  If `CheckPassword` returns False, then it returns `Invalid vault password provided`.  So `CheckPassword` is probably a good place to dig deeper.

Since `CheckPassword` belongs to the `VaultManager` class, let's take a look at `VaultManager.java`.

VaultManager.java:
```java
package com.bsidespdx.flagvault;

public class VaultManager {
    public static String cipherText = "e+aJggifvYOZCTlZKy6uVkuzqTnkJY4JCE45IG0vVIcK8D7+Smv5qqKpgfhuRuL3";

    public static boolean CheckPassword(String str) {
        if (str.length() == 26 && str.charAt(0) == 'l' && str.charAt(1) + str.charAt(2) == 217 && (str.charAt(0) ^ str.charAt(2)) == 24 && (str.charAt(1) ^ str.charAt(3)) == ':' && str.charAt(3) == str.charAt(6) && str.charAt(6) - '1' == str.charAt(9) && (str.charAt(4) ^ 'm') == 0 && str.charAt(5) + 8 == str.charAt(4) && (str.charAt(9) * 5) + (str.charAt(6) * 9) == 1085 && (str.charAt(6) * 8) - (str.charAt(7) * 3) == 445 && str.charAt(10) == str.charAt(0) && str.charAt(11) + 4 == 55) {
            if ((str.charAt(11) ^ str.charAt(12)) == 0 && str.charAt(2) == str.charAt(13) && str.charAt(4) == str.charAt(15) && str.charAt(16) == str.charAt(12) && str.charAt(14) == str.charAt(6) && str.charAt(17) == str.charAt(14) && str.substring(18, 20).equals(str.substring(7, 9).toUpperCase()) && str.charAt(20) * 9 == 297 && str.charAt(20) == str.charAt(21) && str.charAt(21) == str.charAt(22) && str.substring(20, 23).equals(str.substring(23, 26)) && str.charAt(8) * 1337 == 147070) {
                return true;
            }
            return false;
        }
        return false;
    }

    public static String DecryptFlag(String str) {
        return AES.decrypt(cipherText, str);
    }
}
```

Yikes!  That's some messy looking code!  There's two massive if statements, if either statement is false, then the function also returns false.  So we could actually combine these two statements into one, or even better, let's break-apart the problem and seperate them into many!  If we seperate each check by `&&` we will get a bunch of smaller checks to individually try to pass.

```
str.length() == 26
str.charAt(0) == 'l'
str.charAt(1) + str.charAt(2) == 217
(str.charAt(0) ^ str.charAt(2)) == 24
(str.charAt(1) ^ str.charAt(3)) == ':'
str.charAt(3) == str.charAt(6)
str.charAt(6) - '1' == str.charAt(9)
(str.charAt(4) ^ 'm') == 0
str.charAt(5) + 8 == str.charAt(4)
(str.charAt(9) * 5) + (str.charAt(6) * 9) == 1085
(str.charAt(6) * 8) - (str.charAt(7) * 3) == 445
str.charAt(10) == str.charAt(0)
str.charAt(11) + 4 == 55)
str.charAt(11) ^ str.charAt(12)) == 0
str.charAt(2) == str.charAt(13)
str.charAt(4) == str.charAt(15)
str.charAt(16) == str.charAt(12)
str.charAt(14) == str.charAt(6)
str.charAt(17) == str.charAt(14)
str.substring(18, 20).equals(str.substring(7, 9).toUpperCase())
str.charAt(20) * 9 == 297
str.charAt(20) == str.charAt(21)
str.charAt(21) == str.charAt(22)
str.substring(20, 23).equals(str.substring(23, 26))
str.charAt(8) * 1337 == 147070
```

The first check, is to ensure that the password length is 26 characters.  The next check is pretty straightforward too, `str.charAt(0) == 'l'`, the first character must be `l`!  However, things quickly get tricky on the next check, `str.charAt(1) + str.charAt(2) == 217`.  I don't know what the character at index 1 or 2 is, how is this supposed to help?  I can add lots of combinations of numbers to end up with a result of 217!  Let's look at the next line: `(str.charAt(0) ^ str.charAt(2)) == 24`: since I know the character at index 0 is equal to `l`, then I have to figure out what to XoR with that to result in `24`.  So for starters, it's worth mentioning that every ASCII character can actually be represented as a decimal number.  You can look this up using an [ASCII table](http://www.asciitable.com/) or by entering `man ascii` in a Linux terminal, but I personally find it more convenient to just use an interactive Python terminal:

```
>>> ord('l')
108
```

Ok, so now we can convert the statement `(str.charAt(0) ^ str.charAt(2)) == 24` -> `108 ^ str.charAt(2) == 24`.  You could write a quick python script that bruteforces numbers until you find one that will result in `24`, but there's actually an interesting property to the xor operation.  If xor either of the numbers with the result, then it will return the value of the other.  So in other words, we can convert `108 ^ str.charAt(2) == 24` -> `str.charAt(2) == 24 ^ 108`.  Well now that's a much easier operation to solve for!

```
>>> 24 ^ 108
116
```

Using an ASCII table or python, you can also figure out what character that is:

```
>>> chr(116)
't'
```

So now we know the character at index 2 is equal to `t`.  This is getting hard to keep straight though, so let's start writing down the characters we've solved for so far!

```
0  - 108
1  - *
2  - 116
3  - *
4  - *
5  - *
6  - *
7  - *
8  - *
9  - *
10 - *
11 - *
12 - *
13 - *
14 - *
15 - *
16 - *
17 - *
18 - *
19 - *
20 - *
21 - *
22 - *
23 - *
24 - *
25 - *
```

And these are the remaining operation we have to solve for:

```
str.charAt(1) + str.charAt(2) == 217
(str.charAt(1) ^ str.charAt(3)) == ':'
str.charAt(3) == str.charAt(6)
str.charAt(6) - '1' == str.charAt(9)
(str.charAt(4) ^ 'm') == 0
str.charAt(5) + 8 == str.charAt(4)
(str.charAt(9) * 5) + (str.charAt(6) * 9) == 1085
(str.charAt(6) * 8) - (str.charAt(7) * 3) == 445
str.charAt(10) == str.charAt(0)
str.charAt(11) + 4 == 55)
str.charAt(11) ^ str.charAt(12)) == 0
str.charAt(2) == str.charAt(13)
str.charAt(4) == str.charAt(15)
str.charAt(16) == str.charAt(12)
str.charAt(14) == str.charAt(6)
str.charAt(17) == str.charAt(14)
str.substring(18, 20).equals(str.substring(7, 9).toUpperCase())
str.charAt(20) * 9 == 297
str.charAt(20) == str.charAt(21)
str.charAt(21) == str.charAt(22)
str.substring(20, 23).equals(str.substring(23, 26))
str.charAt(8) * 1337 == 147070
```

Now we can solve for `str.charAt(1) + str.charAt(2) == 217` since we have the value for `str.charAt(2)`.

```
str.charAt(1) + str.charAt(2) == 217
x_1 + 116 == 217
x_1 == 217 - 116
x_1 == 101
```

```
(str.charAt(1) ^ str.charAt(3)) == ':'
101 ^ x_3 == ':'
101 ^ x_3 == 58
101 ^ 58 == x_3
95 == x_3
```

```
str.charAt(3) == str.charAt(6)
95 == x_6
```

Let's update our table with x_1, x_3, and x_6:

```
0  - 108
1  - 101
2  - 116
3  - 95
4  - *
5  - *
6  - 95
7  - *
8  - *
9  - *
10 - *
11 - *
12 - *
13 - *
14 - *
15 - *
16 - *
17 - *
18 - *
19 - *
20 - *
21 - *
22 - *
23 - *
24 - *
25 - *
```

```
str.charAt(6) - '1' == str.charAt(9)
x_6 - '1' == x_9
x_6 - 49 == x_9
95 - 49 == x_9
46 == x_9
```

```
(str.charAt(4) ^ 'm') == 0
x_4 ^ 'm' == 0
x_4 ^ 109 == 0
109 ^ 0 == x_4
109 == x_4
```

```
str.charAt(5) + 8 == str.charAt(4)
x_5 + 8 == x_4
x_5 + 8 == 109
x_5 == 109 - 8
x_5 == 101
```

```
(str.charAt(9) * 5) + (str.charAt(6) * 9) == 1085
x_9*5 + x_6*9 == 1085
x_9*5 + 95*9 == 1085
x_9*5 + 855 == 1085
x_9*5 == 1085 - 855
x_9*5 == 230
x_9 == 230/5 == 46
```

```
(str.charAt(6) * 8) - (str.charAt(7) * 3) == 445
x_6*8 - x_7*3 == 445
95*8 - x_7*3 == 445
760 - x_7*3 == 445
760 - 445 == x_7*3
315 == x_7*3
315/3 == x_7
105 == x_7
```

Let's update our table again with x_9, x_4, x_5, x_6, and x_7.

```
0  - 108
1  - 101
2  - 116
3  - 95
4  - 109
5  - 101
6  - 95
7  - 105
8  - *
9  - 46
10 - *
11 - *
12 - *
13 - *
14 - *
15 - *
16 - *
17 - *
18 - *
19 - *
20 - *
21 - *
22 - *
23 - *
24 - *
25 - *
```

And these are the remaining to solve:

```
str.charAt(10) == str.charAt(0)
str.charAt(11) + 4 == 55)
str.charAt(11) ^ str.charAt(12)) == 0
str.charAt(2) == str.charAt(13)
str.charAt(4) == str.charAt(15)
str.charAt(16) == str.charAt(12)
str.charAt(14) == str.charAt(6)
str.charAt(17) == str.charAt(14)
str.substring(18, 20).equals(str.substring(7, 9).toUpperCase())
str.charAt(20) * 9 == 297
str.charAt(20) == str.charAt(21)
str.charAt(21) == str.charAt(22)
str.substring(20, 23).equals(str.substring(23, 26))
str.charAt(8) * 1337 == 147070
```

Most of these are similar to one's we've already solved above or simpler, so for brevity I will skip most of these, however I will focus on the last 6.

```
str.substring(18, 20).equals(str.substring(7, 9).toUpperCase())
```

This is basically saying that the characters at index 18,19 should be equal to the characters at index 7,8, but capitalized.  We already have 7, but the last line gives us 8: `str.charAt(8) * 1337 == 147070` which is `147070/1337==110`.  So converting 7 and 8 to characters using an ascii table we get `in`.  So that means if these are capitalized, then the characters at 18,19 are `IN`.

```
str.charAt(20) * 9 == 297
x_20 == 297/9 == 33 == '!'
```

Then the following two statements:

```
str.charAt(20) == str.charAt(21)
str.charAt(21) == str.charAt(22)
```

Mean that characters at index 20, 21, and 22 are all the same, so `!`.

So now once you convert your table of integers to their ascii characters, you should have the password: `let_me_in.l33t_m3_IN!!!!!!`.

We're almost there, this should be our decryption key!

## Decrypting the flag

So now that we have the encryption key, how do we decrypt the flag?  If you have an Android phone or an emulator setup, you could simply install the APK and manually type in the password.  But let's also look at how we can decrypt it without either!

Let's revist the use of the password:

```java
textView.setText(VaultManager.CheckPassword(obj) ? VaultManager.DecryptFlag(obj) : "Invalid vault password provided");
```

So we just need to call `VaultManager.DecryptFlag(obj)` with `"let_me_in.l33t_m3_IN!!!!!!"` as the argument.  Let's look at this function.

```java
public static String cipherText = "e+aJggifvYOZCTlZKy6uVkuzqTnkJY4JCE45IG0vVIcK8D7+Smv5qqKpgfhuRuL3";

....

    public static String DecryptFlag(String str) {
        return AES.decrypt(cipherText, str);
    }
```

So we will need to look at the AES class in `AES.java`.

```java
package com.bsidespdx.flagvault;

import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Base64;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

public class AES {
    private static byte[] key;
    private static SecretKeySpec secretKey;

    public static void setKey(String str) {
        try {
            key = str.getBytes("UTF-8");
            byte[] digest = MessageDigest.getInstance("SHA-1").digest(key);
            key = digest;
            key = Arrays.copyOf(digest, 16);
            secretKey = new SecretKeySpec(key, "AES");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e2) {
            e2.printStackTrace();
        }
    }

    public static String encrypt(String str, String str2) {
        try {
            setKey(str2);
            Cipher instance = Cipher.getInstance("AES/ECB/PKCS5Padding");
            instance.init(1, secretKey);
            return Base64.getEncoder().encodeToString(instance.doFinal(str.getBytes("UTF-8")));
        } catch (Exception e) {
            PrintStream printStream = System.out;
            StringBuilder sb = new StringBuilder();
            sb.append("Error while encrypting: ");
            sb.append(e.toString());
            printStream.println(sb.toString());
            return null;
        }
    }

    public static String decrypt(String str, String str2) {
        try {
            setKey(str2);
            Cipher instance = Cipher.getInstance("AES/ECB/PKCS5PADDING");
            instance.init(2, secretKey);
            return new String(instance.doFinal(Base64.getDecoder().decode(str)));
        } catch (Exception e) {
            PrintStream printStream = System.out;
            StringBuilder sb = new StringBuilder();
            sb.append("Error while decrypting: ");
            sb.append(e.toString());
            printStream.println(sb.toString());
            return null;
        }
    }
}
```

Since this class doesn't import any Android-specific libraries, we can actually just compile and run this directly on our host.

Let's add a main function to the class first though!  I just grabbed a Java hello world from the first [google result](https://introcs.cs.princeton.edu/java/11hello/) and tweaked it to print the result of `decrypt`.

```java
public class AES {
...
   public static void main(String[] args) {
      System.out.println(decrypt("e+aJggifvYOZCTlZKy6uVkuzqTnkJY4JCE45IG0vVIcK8D7+Smv5qqKpgfhuRuL3", "let_me_in.l33t_m3_IN!!!!!!"));
   }
}
```

And remove `package com.bsidespdx.flagvault;` from the top of the source file.

Finally, compile and run it!

```bash
javac AES.java
java AES
BSidesPDX{g00d_crypt0_1s_h4rd_70_d0!>>}
```

Flag: `BSidesPDX{g00d_crypt0_1s_h4rd_70_d0!>>}`

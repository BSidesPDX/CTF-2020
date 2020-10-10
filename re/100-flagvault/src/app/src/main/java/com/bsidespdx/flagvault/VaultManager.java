package com.bsidespdx.flagvault;

import android.util.Log;

public class VaultManager {
    public static String cipherText = "e+aJggifvYOZCTlZKy6uVkuzqTnkJY4JCE45IG0vVIcK8D7+Smv5qqKpgfhuRuL3";

    public static boolean CheckPassword(String s) {
        if (s.length() != 26) {
            return false;
        }

        if (s.charAt(0) == 'l') {
            if ((s.charAt(1) + s.charAt(2)) == 217){
                if ((s.charAt(0) ^ s.charAt(2)) == 24) {
                    if ((s.charAt(1) ^ s.charAt(3)) == 58) {
                        if (s.charAt(3) == s.charAt(6)) {
                            if ((s.charAt(6) - 49) == s.charAt(9)) {
                                if ((s.charAt(4) ^ 109) == 0) {
                                    if (s.charAt(5) + 8 == s.charAt(4)) {
                                        if ((s.charAt(9) * 5) + (s.charAt(6)*9) == 1085) {
                                            if ((s.charAt(6)*8) - (s.charAt(7)*3) == 445) {
                                                if (s.charAt(10) == s.charAt(0)) {
                                                    if (s.charAt(11) + 4 == 55) {
                                                        if ((s.charAt(12) ^ s.charAt(11)) == 0) {
                                                            if (s.charAt(2) == s.charAt(13)) {
                                                                if (s.charAt(4) == s.charAt(15)) {
                                                                    if (s.charAt(16) == s.charAt(12)) {
                                                                        if (s.charAt(14) == s.charAt(6)) {
                                                                            if (s.charAt(17) == s.charAt(14)) {
                                                                                if (s.substring(18,20).equals(s.substring(7,9).toUpperCase())) {
                                                                                    if (s.charAt(20) * 9 == 297) {
                                                                                        if (s.charAt(20) == s.charAt(21) && s.charAt(21) == s.charAt(22)) {
                                                                                            if (s.substring(20,23).equals(s.substring(23,26))) {
                                                                                                if (s.charAt(8)*1337 == 147070) {
                                                                                                    return true;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    public static String DecryptFlag(String key) {
        return AES.decrypt(cipherText, key);
    }
}

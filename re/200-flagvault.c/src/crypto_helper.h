/* Encryption/Decryption */
void hashpassword(char* pw, unsigned char* digest, int digestlen);
void enc(char* plaintxt_fn, char* ciphertxt_fn, char* pw);
void dec(char* cipher_fn, char* output_fn, char* pw);

/* Encryption Consts */
#ifndef KEY_LEN
#define KEY_LEN     16
#endif

#ifndef IV_LEN
#define IV_LEN      12
#endif

#ifndef TAG_LEN
#define TAG_LEN     16
#endif

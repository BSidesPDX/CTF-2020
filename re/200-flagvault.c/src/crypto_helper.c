#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <assert.h>

#include "crypto_helper.h"

/*
 * Encrypt the provided plaintext with the provided password
 */
void enc(char* plaintxt_fn, char* ciphertxt_fn, char* pw) {
    int ret;
    int outlen;
    int plaintxtlen;
    FILE *infile;
    FILE *outfile;
    int filesize;
    unsigned char iv[IV_LEN];
    unsigned char tag[TAG_LEN];
    unsigned char* key;
    unsigned char* plaintxt_data;
    unsigned char* ciphertxt_data;
    unsigned char* outbuf;

    /* read plaintxt data from file */
    infile = fopen(plaintxt_fn, "rb");
    fseek(infile, 0L, SEEK_END);
    filesize = ftell(infile);
    rewind(infile);
    plaintxt_data = (unsigned char *) malloc(filesize);
    fread(plaintxt_data, 1, filesize, infile); 
    plaintxtlen = filesize;
    fclose(infile);

    /* initialize cipher output and outbuf */
    ciphertxt_data = (unsigned char *) malloc(filesize);
    outbuf = (unsigned char *) malloc(filesize);

    /* generate keyhash */
    key = (unsigned char *) malloc(sizeof(unsigned char) * KEY_LEN);
    hashpassword(pw, key, KEY_LEN);
    if (key == NULL) {
        printf("Failed to generate crypto hash password\n");
        return;
    }

    /* generate a new, random IV */
    if (!RAND_bytes(iv, sizeof(iv))) {
        /* OpenSSL reports a failure, act accordingly */
        printf("Failed to generate a random IV\n");
        return;
    }

    /* create cipher objects */
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    /* initialize encryption type (AES-128 GCM) */
    ret = EVP_EncryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL);
    assert(ret == 1);
    /* set IV Len */
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL);
    assert(ret == 1);
    /* initialize key and IV */
    ret = EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    assert(ret == 1);
    /* encrypt the plaintext*/
    ret = EVP_EncryptUpdate(ctx, outbuf, &outlen, plaintxt_data, plaintxtlen);
    assert(ret == 1);
    /* finalise */
    ret = EVP_EncryptFinal_ex(ctx, outbuf, &outlen);
    assert(ret == 1);
    /* copy outbuf to ciphertxt_data */
    memcpy(ciphertxt_data, outbuf, plaintxtlen);
    /* get the tag*/
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, outbuf);
    assert(ret == 1);
    /* copy outbuf to tag_data */
    memcpy(tag, outbuf, TAG_LEN);
    /* free */
    EVP_CIPHER_CTX_free(ctx);

    /* write iv and ciphertext to file */
    outfile = fopen(ciphertxt_fn, "wb");
    fwrite((const char*)iv, sizeof(iv), 1, outfile);
    fwrite((const char*)tag, TAG_LEN, 1, outfile);
    fwrite((const char*)ciphertxt_data, 1, plaintxtlen, outfile);
    fclose(outfile);

    /* Print info message */
    printf("Successfully encrypted %d bytes of data\n", plaintxtlen);
}

/*
 * Decrpyt the cipher file with provided password
 */
void dec(char* cipher_fn, char* output_fn, char* pw) {
    int outlen;
    int ret;
    int cipherlen;
    FILE *infile;
    FILE *outfile;
    int filesize;
    unsigned char* key;
    unsigned char* filedata;
    unsigned char* ciphertxt;
    unsigned char* outbuf;
    unsigned char iv[IV_LEN];
    unsigned char tag[TAG_LEN];
    EVP_CIPHER_CTX *ctx;

    /* read raw data from file */
    infile = fopen(cipher_fn, "rb");
    infile = fopen(cipher_fn, "rb");
    fseek(infile, 0L, SEEK_END);
    filesize = ftell(infile);
    rewind(infile);
    filedata = (unsigned char *) malloc(filesize);
    fread(filedata, 1, filesize, infile);
    fclose(infile);

    /* format: [ (16b iv) (16b tag) (rest is cipher...) ] */
    cipherlen = (int)filesize-sizeof(iv)-sizeof(tag);
    ciphertxt = (unsigned char *) malloc(cipherlen);
    outbuf = (unsigned char *) malloc(filesize);
    memcpy(iv, filedata, sizeof(iv));
    memcpy(tag, filedata+sizeof(iv), sizeof(tag));
    memcpy(ciphertxt, filedata+sizeof(iv)+sizeof(tag), cipherlen);

    /* build key hash */
    key = (unsigned char *) malloc(sizeof(unsigned char) * KEY_LEN);
    hashpassword(pw, key, KEY_LEN);
    if (key == NULL) {
        printf("Failed to generate crypto hash password\n");
        return;
    }

    /* create cipher objects */
    ctx = EVP_CIPHER_CTX_new();
    /* setup encryption type (AES-128 GCM) */
    ret = EVP_DecryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL);
    assert(ret == 1);
    /* set IV length */
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL);
    assert(ret == 1);
    /* initialize with enc key + iv */
    ret = EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);
    assert(ret == 1);
    /* input ciphertxt */
    ret = EVP_DecryptUpdate(ctx, outbuf, &outlen, ciphertxt, cipherlen);
    assert(ret == 1);
    /* set expected tag */
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, sizeof(tag), tag);
    /* Finalise */
    ret = EVP_DecryptFinal_ex(ctx, outbuf, &outlen);

    /* check tag */
    if (ret <= 0) {
        printf("Tag verify has failed!!\n");
        return;
    }

    /* free */
    EVP_CIPHER_CTX_free(ctx);

    /* write decrypted plaintext to file */
    outfile = fopen(output_fn, "wb");
    fwrite((const char*)outbuf, 1, cipherlen, outfile);
    fclose(outfile);

    /* Print info message */
    printf("Decrypted %d bytes of data\n", cipherlen);
}

/*
 * Hash the provided password with PKCS5_PBKDF2_HMAC_SHA1
 */
void hashpassword(char* pw, unsigned char* digest, int digestlen) {
    long iterations = 10000;
    unsigned char salt[] = {'b','a','r','f'};
    PKCS5_PBKDF2_HMAC_SHA1(pw, strlen(pw), salt, sizeof(salt), iterations, digestlen, digest);
}

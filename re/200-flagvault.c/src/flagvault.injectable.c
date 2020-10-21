#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "crypto_helper.h"

char USAGE[] = "Usage:\n\n  ::Encrypt::\n\t./flagvault -e -p <plaintxtfile (input)> -c <encryptedfile (output)>\n  ::Decrypt::\n\t./flagvault -d -c <encryptedfile (input)> -p <plaintxtfile (output)>\n";

const char verify_password_b[] = "";

//bool verify_password(char* password, int password_length);

void usage() {
    printf("\n%s\n", USAGE);
}

int printerror(const char* errmsg) {
    printf("Error: %s\n", errmsg);
    return -1;
}

int main(int argc, char** argv) {
    int opt;
    char* plaintxtfile      = NULL;
    char* encryptedfile     = NULL;
    bool isencrypt = false;
    bool isdecrypt = false;
    char password [128];
    int password_length = 0;

    const char* short_opt = "hedp:c:";

    //Parse the arguments
    while ((opt = getopt(argc, argv, short_opt)) != -1)
    {
        switch (opt)
        {
            case 'e':
                isencrypt = true;
                break;
            case 'd':
                isdecrypt = true;
                break;
            case 'p':
                plaintxtfile = optarg;
                break;
            case 'c':
                encryptedfile = optarg;
                break;
            case 'h':
                usage();
                return 1;
        }
    }

    /* error check the operation */
    if (isencrypt == true && isdecrypt == true)
    {
        usage();
        return printerror("Can not use both -e(encrypt) and -d(decrypt) arguments at the same time\n");
    }

    if (plaintxtfile == NULL || encryptedfile == NULL)
    {
        usage();
        return printerror("Must specifiy both an encryptedfile and a plaintextfile\n");
    }

    printf("Enter password: ");
    scanf("%127s", password);
    password_length = strlen(password);

    if (isencrypt)
    {
        enc(plaintxtfile, encryptedfile, password);
    }
    else if (isdecrypt)
    {
        // start uncryptoring
        char *code = (unsigned char *) malloc(sizeof(verify_password_b));
        for (int i=0; i<sizeof(verify_password_b); i++)
        {
            code[i] = verify_password_b[i] ^ 0x66;
        }
        void *mem = mmap(0, sizeof(verify_password_b), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
        memcpy(mem, code, sizeof(verify_password_b));
        mprotect(mem, sizeof(verify_password_b), PROT_READ|PROT_EXEC);
        //bool verify_password(char* password, int password_length);
        bool (*verify_password)(char*, int) = (bool(*)(char*, int))mem;


        if (verify_password(password, password_length))
        {
            dec(encryptedfile, plaintxtfile, password);
        }
        else
        {
            printf("Wrong password supplied!\n");
        }
    }
    else
    {
        usage();
        return printerror("Missing either -e(encrypt) or -d(decrypt) argument\n");
    }

    return 0;
}

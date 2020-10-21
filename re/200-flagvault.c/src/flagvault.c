#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "crypto_helper.h"

char USAGE[] = "Usage:\n\n  ::Encrypt::\n\t./flagvault -e -p <plaintxtfile (input)> -c <encryptedfile (output)>\n  ::Decrypt::\n\t./flagvault -d -c <encryptedfile (input)> -p <plaintxtfile (output)>\n";

bool verify_password(char* password, int password_length)
{
    // Target Password: n0b0dy_g3tz_h4ck3d!
    if (password_length != 19)
    {
        return false;
    }
    //n
    if (password[0] != 'n')
    {
        return false;
    }
    //0
    if (password[1] != '0')
    {
        return false;
    }
    //b
    if (password[2] != 'b')
    {
        return false;
    }
    //0
    if (password[3] != password[1])
    {
        return false;
    }
    //d
    if (password[4] != 'd')
    {
        return false;
    }
    //y
    if (password[5] != password[4]+21)
    {
        return false;
    }
    //_
    if (password[6] != password[1]+47)
    {
        return false;
    }
    //g
    if (password[7] != password[6]+8)
    {
        return false;
    }
    //3
    if (password[8] != password[1] + 3)
    {
        return false;
    }
    //t
    if ((password[9] ^ 't') != 0x00)
    {
        return false;
    }
    //z
    if ((password[10] ^ password[9]) != 14)
    {
        return false;
    }
    //_
    if (password[11] != password[6])
    {
        return false;
    }
    //h
    if (password[12] != 'h')
    {
        return false;
    }
    //4
    if (password[13] != password[8]+1)
    {
        return false;
    }
    //c
    if ((password[14] ^ 'c') != 0x00)
    {
        return false;
    }
    //k
    if (password[15] != 'k')
    {
        return false;
    }
    //3
    if (password[16] != password[8])
    {
        return false;
    }
    //d
    if (password[17] != password[14]+1)
    {
        return false;
    }
    //!
    if (password[18] != '!')
    {
        return false;
    }
    return true;
}

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
        // todo -- perform a password check
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

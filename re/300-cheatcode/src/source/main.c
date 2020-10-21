#include <string.h>
#include <stdio.h>

#include <switch.h>

#define KONAMI_CHEAT_CODE_LENGTH 10
#define CHEAT_CODE_FLAG_LENGTH 11
#define FLAG_LENGTH 75
#define XKEY "\x01\x04\xff\xff\x02"
#define ART "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@@@@@@@@@//(# . @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@@@@@@@*(/&&&%# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@@@@@@ .//*(&%/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@ * * ,/./*//,/  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@ //   @% ///* /*   *//**/,@@%%%%%%@@@%%%%@%%%%%%%@@@%%%%%%%@@%%%%%%@@@@@@@" \
"@@@@@@@@ /.@ //*///*// #% #####@ ######## #### @########.@###### @########(@@@@@" \
"@@@@@@@@@@@ ./*//./// .,/#  ###@ ###.@@@@@#### @### @###.@###(@@@@###.@@@@@@@@@@" \
"@@@@@@@@@@  ,/,/,/// @.#######.@ ######## #### @### @###.@###### @########(@@@@@" \
"@@@@@@@@@@@ ,/.@ ** @@.###@ ###@    . ### #### @### @###.@###(@@@@    @###(@@@@@" \
"@@@@@@@@@@@@ *.@,/ @@@.########@ ######## #### @########.@######.@########(@@@@@" \
"@@@@@@@@@@@@ /, * @@@@ ,,,,.& ,,*,.@ ,,,,.@/,,.@@@@,,  ,,,,,( ,, .,. ,,,,, @@@@@" \
"@@@@@@@@@@@@#/ / @@@@@.#/@## (#.###@.#*@##*,## ###@##  ##@##  ##@##  ##@## @@@@@" \
"@@@@@@@@@@@@@*//@@@@@@.##   @(#.###@.#/ ##*/##..#/@##  ## ##  ##@##  ##@## @@@@@" \
"@@@@@@@@@@@@ ,//@@@@@@.#/@@@@(#####@.#*@##*/#####/@##  ##@##  ##@##  ##### @@@@@" \
"@@@@@@@@@@@ ,*,*@@@@@@@@@@@@@@@@@@@@@@@@#########/@######### @@@@######### @@@@@" \
"@@@@@@@@@(/# / . @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \
"@@@@@@@@@@@( @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" \

s32 CIPHER_BLOCK[FLAG_LENGTH] = {-8190, 7788, 14940, 14280, 11500, 11110, 9085, 19520, 10676, 21120, 12792, 16731, 7920, 17490, 2300, 5280, 4104, 6324, 23690, 7410, 21631, 2052, 510, 15010, 10070, 935, 477, 7370, 12255, 8415, 2304, 13937, 12320, 3315, -935, 2448, 3990, 11537, 9500, 7888, 7696, 2754, -890, 9120, 13400, 3168, 2652, 14964, 9880, 2023, 3900, -3850, 9240, -1425, 3471, 12403, 5695, 17100, 5900, 3990, 6426, -1026, 6909, 16588, 8007, 4655, 11286, 5760, 16800, 408, 4655, -1836, 3264, 9690, 1683};
char CODE_KEY[11] = {0};
char flag[FLAG_LENGTH] = {0};

char get_code_key(u32 keypress)
{
    int i = 0;
    while (i <= 32)
    {
        char tmp = (keypress >> i) & 0xff;
        if (tmp != 0x00)
        {
            return tmp;
        }
        i = i + 4;
    }
    return 0;
}

void decrypt_flag()
{
    int prev = -42;

    for (int i=0; i<FLAG_LENGTH; i++)
    {
        int r = CIPHER_BLOCK[i] / prev;
        r = r + i;
        r = r ^ XKEY[i % 5];
        r = r ^ CODE_KEY[i % 11];
        flag[i] = (char)r;
        prev = r;
    }
}

int main(int argc, char **argv)
{
    u32 cheat_code_konami[KONAMI_CHEAT_CODE_LENGTH] = {KEY_DUP, KEY_DUP, KEY_DDOWN, KEY_DDOWN, KEY_DLEFT, KEY_DRIGHT, KEY_DLEFT, KEY_DRIGHT, KEY_B, KEY_A};
    u32 cheat_code_flag[CHEAT_CODE_FLAG_LENGTH] = {KEY_DDOWN, KEY_DUP, KEY_DUP, KEY_DLEFT, KEY_DLEFT, KEY_A, KEY_A, KEY_DRIGHT, KEY_B, KEY_DDOWN, KEY_DLEFT};
    u32 cheat_position = 0;
    bool cheat_is_konami = false;

    consoleInit(NULL);

    u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame

    printf("\x1b[1;1HEnter the secret cheat code to reveal the flag.");

    // Main loop
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        //hidKeysHeld returns information about which buttons have are held down in this frame
        u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
        //hidKeysUp returns information about which buttons have been just released
        u64 kUp = hidKeysUp(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        //Do the keys printing only if keys have changed
        if (kDown != kDownOld || kHeld != kHeldOld || kUp != kUpOld)
        {
            if (kUp != 0)
            {
                CODE_KEY[cheat_position] = get_code_key(kUp);
                if (cheat_position == 0)
                {
                    if (kUp == KEY_DUP)
                    {
                        cheat_is_konami = true;
                        cheat_position = 1;
                    }
                    else if (kUp == KEY_DDOWN)
                    {
                        cheat_is_konami = false;
                        cheat_position = 1;
                    }
                }
                else if (cheat_position > 0)
                {
                    if (cheat_is_konami)
                    {
                        if (kUp == cheat_code_konami[cheat_position])
                        {
                            cheat_position += 1;
                            if (cheat_position == KONAMI_CHEAT_CODE_LENGTH)
                            {
                                consoleClear();
                                printf("\x1b[1;1HNice try, it's a little harder than that");
                                cheat_position = 0;
                                cheat_is_konami = false;
                            }
                        } else {
                            cheat_position = 0;
                        }

                    }
                    else
                    {
                        if (kUp == cheat_code_flag[cheat_position])
                        {
                            cheat_position += 1;
                            if (cheat_position == CHEAT_CODE_FLAG_LENGTH)
                            {
                                consoleClear();
                                decrypt_flag();
                                printf("%s\n", ART);
                                printf("%s\n", flag);
                            }
                        } else {
                            cheat_position = 0;
                        }
                    }
                }
            }
        }

        //Set keys old values for the next frame
        kDownOld = kDown;
        kHeldOld = kHeld;
        kUpOld = kUp;

        JoystickPosition pos_left, pos_right;

        //Read the joysticks' position
        hidJoystickRead(&pos_left, CONTROLLER_P1_AUTO, JOYSTICK_LEFT);
        hidJoystickRead(&pos_right, CONTROLLER_P1_AUTO, JOYSTICK_RIGHT);

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}

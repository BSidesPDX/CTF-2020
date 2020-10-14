#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SPEAKERS 20
#define MAX_NAME_SIZE 50
#define MAX_DESCRIPTION_SIZE 0x100

#define TRUE 1
#define FALSE 0

struct Speaker {
    int id;
    char *name;
    char *description;
};

struct Speaker *speakers[MAX_SPEAKERS];

struct Speaker *get_speaker(int is_new_speaker) {
    while (1) {
        printf("Enter the speaker ID: ");

        int sid = -1;
        scanf("%d", &sid);

        if (sid == -1) {
            printf("Goodbye!\n");
            exit(0);
        } else {
            if (sid < 0) {
                printf("You fool!\n");
            } else if (sid >= MAX_SPEAKERS) {
                printf("You don't have enough people attending your conference to need %d speaker slots. Stay between 0 and %d.\n", sid, MAX_SPEAKERS - 1);
            } else if (is_new_speaker) {
                struct Speaker *speaker;
                speaker = malloc(sizeof(struct Speaker));
                speaker->id = sid;
                return speaker;
            } else if (speakers[sid] == NULL) {
                printf("Speaker ID %d has not been registered yet.\n", sid);
            } else {
                return speakers[sid];
            }
        }
    }
}

void view_speaker(struct Speaker *speaker) {
    printf("%d\t:: %s\t:: %s\n", speaker->id, speaker->name, speaker->description);
}

void edit_speaker(struct Speaker *speaker) {
    if (speaker->name) {
        free(speaker->name);
    }
    printf("Enter a name: ");
    speaker->name = malloc(MAX_NAME_SIZE);
    read(0, speaker->name, MAX_NAME_SIZE); // VULN: null byte overflow
    strtok(speaker->name, "\n");

    if (speaker->description) {
        free(speaker->description);
    }
    printf("Enter a bio: ");
    speaker->description = malloc(MAX_DESCRIPTION_SIZE);
    read(0, speaker->description, MAX_DESCRIPTION_SIZE); // VULN: null byte overflow
    strtok(speaker->description, "\n");
}

int main() {
    setbuf(stdout, NULL);
    alarm(120);

    for (int i = 0; i < MAX_SPEAKERS; i++) {
        speakers[i] = NULL;
    }

    printf("Hello, and welcome to the BSidesPDX conference speaker management system.\n\n");
    
    while (TRUE) {
        printf("Which of the following options would you like to do?\n");
        printf("1. Create a new speaker profile\n");
        printf("2. Update a speaker profile\n");
        printf("3. Delete a speaker profile\n");
        printf("4. View all speakers\n");
        printf("5. Exit");

        printf("\n> ");
        int selection;
        scanf("%d", &selection);
        printf("\n");

        struct Speaker *speaker;

        switch (selection) {
            // create a speaker profile
            case 1:
                speaker = get_speaker(TRUE);
                edit_speaker(speaker);
                speakers[speaker->id] = speaker;
            break;

            // update a speaker profile
            case 2:
                speaker = get_speaker(FALSE);
                printf("Editing speaker: ");
                view_speaker(speaker);
                edit_speaker(speaker);
            break;
            
            // delete a speaker profile
            case 3:
                speaker = get_speaker(FALSE);
                if (speaker->name) {
                    free(speaker->name);
                }
                if (speaker->description) {
                    free(speaker->description);
                }
                speakers[speaker->id] = NULL;
                free(speaker);
            break;

            // view all speakers
            case 4:
                printf("Here are all of the registered speakers:\n");
                for (int i = 0; i < MAX_SPEAKERS; i++) {
                    if (speakers[i] != NULL) {
                        speaker = speakers[i];
                        view_speaker(speaker);
                    }
                }
            break;

            // exit
            case 5:
                printf("Goodbye!\n");
                exit(0);
            break;
            
            default:
                printf("Invalid selection. Please try again.\n");
            break;
        }

        printf("\n");
    }

    return 0;
}

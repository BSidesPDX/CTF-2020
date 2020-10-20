#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPEAKERS 20

void create();
void delete();
void view();
void quit();
int getidx();

int counter = 0;
char* arr[MAX_SPEAKERS];

int main() {
    int choice;
    int ops;

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    alarm(120);

    printf("Welcome to the BSidesPDX Speaker Management software.\n* You can determine which libc version remote is running using the provided Dockerfile or by leaking an address from remote.\n* Learn about the heap here: https://azeria-labs.com/heap-exploitation-part-2-glibc-heap-free-bins/\n* If you can, use gdb-gef's excellent `heap bins` / `heap chunks` commands to debug your solve script.\n* Hint: to pwn this, basicaly, figure out how to implement a House of Botcake style attack\nGood luck!\n");

    ops = 0;
    while(1) {
        if(ops >= 100) {
            printf("Do you even know how to use this software?\n");
            _exit(0);
        }

        printf("\n1. Register speaker\n2. Delete speaker\n3. View speaker\n4. Exit\n\n");
        ops++;

        printf("> ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
            create();
            break;

            case 2:
            delete();
            break;

            case 3: 
            view();
            break;

            case 4:
            quit();
        }
    }
}

int getidx() {
    int idx;

    printf("Which speaker ID? ");
    scanf("%d", &idx);

    if(idx < 0 || idx >= MAX_SPEAKERS) {
        printf("Try again.\n");
        idx = getidx();
    }

    return idx;
}

void create() {
    int idx;
    int size;
    int amt;

    idx = getidx();

    printf("How long is the speaker name? ");
    scanf("%d", &size);
    getchar();

    if(size <= 0 || size > 0x200) {
        printf("Invalid size\n");
        _exit(0);
    }

    arr[idx] = (char*) malloc(size);
    // printf("arr[%d] =\tmalloc(%x):\t%p\n", idx, size, arr[idx]);

    printf("What is the speaker's name? ");
    amt = read(0, arr[idx], size-1);
    getchar();

    if(amt == -1) {
        printf("Goodbye\n");
        _exit(0);
    }

    arr[idx][amt] = '\x00';
    counter += 1;
}

void delete() {
    int idx;
    int freeagain;

    idx = getidx();
    getchar();
    if (counter > 0) {
        free(arr[idx]);
        // printf("arr[%d] =\tfree(%p):\n", idx, arr[idx]);
        counter -= 1;
    } else {
        return;
    }
}

void view() {
    int idx;

    idx = getidx();

    if (arr[idx]) {
        puts(arr[idx]);
    }
}

void quit() {
    printf("Goodbye\n");
    _exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void win() {
    printf("Good job, you called win()!\n");
    system("/bin/sh");
}

int main() {
    setbuf(stdout, NULL);
    alarm(120);

    char buffer[40];
    printf("You've got a 40-byte buffer to overflow. There is a win() function you should call (TODO: find its address?). Remember to overwrite the base pointer etc!\n\nGet a shell: ");
    gets(buffer);
    printf("I hope your payload was right. Returning...\n");
    return 0;
}

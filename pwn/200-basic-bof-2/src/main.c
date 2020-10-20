#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    setbuf(stdout, NULL);
    alarm(120);

    char *message = "\nUseful resources:\n* https://libc.blukat.me/\n* one_gadget\n* pwntools. This is an intro challenge, but you'll want to know how to use these for future challenges."; // disable optimizations so this stays
    char buffer[40];
    printf("You've got a buffer to overflow. There is no win(), but there is %p.\n\nGet a shell: ", &puts);
    gets(buffer);
    return 0;
}

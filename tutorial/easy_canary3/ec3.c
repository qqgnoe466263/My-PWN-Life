#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * fork? canary?
 */

void init()
{
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void magic()
{
    system("/bin/sh");
}

void bof()
{
    char buf[100];
    read(0, buf,136);
}


int main()
{
    init();

    while (1) {
        if (fork()) {
            wait(0);
        } else {
            puts("HiCanary");
            bof();
            puts("Nice");
        }
    }
    exit(0);
}

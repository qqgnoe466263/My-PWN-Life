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

void bof_again()
{
    char buf[100];
    read(0, buf, 136);
}

void bof()
{
    char buf[100];
    read(0, buf,120);
    int len = strlen(buf);
    write(1, buf, len);
}


int main()
{
    pid_t pid;
    init();

    if (fork()) {
        wait(0);
        bof_again();
    } else {
        bof();
    }

    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char buf1[100];


void init()
{
    setvbuf(stdin , 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void vuln()
{
    char buf[100];
    read(0, buf1, 100);
    read(0, buf, 256);
}

int main()
{
    init();
    write(1, "Hi dl_resolve~\n", 15);
    vuln();

    return 0;
}

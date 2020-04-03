#include <stdio.h>

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


void vuln()
{
    char format[40];
    char buf[100];

    scanf("%40s", format);
    printf(format);

    write(1, "\nwrite again!\n", 14);
    read(0, buf, 256);
}


int main()
{
    init();
    vuln();

    return 0;
}

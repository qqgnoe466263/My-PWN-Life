#include <stdio.h>

char fmt[100];

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

void B()
{
    fgets(fmt, 100, stdin);
    printf(fmt);
}

void A()
{
    B();
}

int main()
{
    init();

    while (1)
        A();

    return 0;
}

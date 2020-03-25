#include <stdio.h>
#include <stdlib.h>

void init()
{
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}

void vuln()
{
    char buf[128];
    write(1, "hello ret2csu!\n",15);
    read(0, buf, 0x200);
}

int main()
{
    init();
    vuln();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Print Return Hijack in One Shot
 * close your ASLR
 */

void b()
{
    char buf[88];
    fgets(buf, sizeof(buf), stdin);
    printf(buf);
    _exit(0);
}

void a()
{
    b();
}

int main()
{
    setvbuf(stdout, 0, _IONBF, 0);
    alarm(180);
    a();

    return 0;
}

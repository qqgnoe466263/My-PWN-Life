#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
 * ret2dlresolve practice from winesap
 * ubuntu 18.04 worked
 */

char buf[10000];

void nouse()
{
    alarm(87);
}

void vuln()
{
    char local[10];
    int len = read(0, buf, sizeof(buf));
    memcpy(local, buf, len);
}

int main()
{
    vuln();

    return 0;
}

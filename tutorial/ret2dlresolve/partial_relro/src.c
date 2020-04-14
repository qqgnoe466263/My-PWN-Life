#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
 * ret2dlresolve practice from winesap
 * ubuntu 18.04 worked
 */

char buf[100000];


int main()
{
    char local[10];
    int len = read(0, buf, sizeof(buf));
    memcpy(local, buf, len);

    return 0;
}

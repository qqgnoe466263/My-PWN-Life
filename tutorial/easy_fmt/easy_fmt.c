#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init()
{
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}

void main()
{
    init();
    char str[200];
    while (fgets(str,sizeof(str),stdin)) {
        printf(str);
    }
    
    exit(0);
}

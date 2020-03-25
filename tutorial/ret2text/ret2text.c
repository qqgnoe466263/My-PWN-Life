#include<stdio.h>

void init()
{
    setvbuf(stdout,0,2,0);
    setvbuf(stdin,0,2,0);
    setvbuf(stderr,0,2,0);
}

void sh()
{
	system("/bin/sh");	
}


int main()
{
	char buf[10];
	init();
	printf("Can u ret2text?\n");
	gets(buf);

	return 0;
}

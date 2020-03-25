#include<stdio.h>

char buf1[100];


void init()
{
	setvbuf(stdin,0,2,0);
	setvbuf(stdout,0,2,0);
	setvbuf(stderr,0,2,0);
}


void vuln()
{
	char buf[100];

	printf("Do you know shellcode?\n");

	gets(buf);
	strcpy(buf1,buf);
}


int main()
{
	init();
	vuln();

	return 0;
}

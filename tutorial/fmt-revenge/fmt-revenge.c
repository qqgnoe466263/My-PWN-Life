#include<stdio.h>

/*
	glibc2.27,ubuntu18.04
	gcc fmt-revenge.c -o fmt-revenge -g -no-pie
	this challenge is from AIS3 EOF 2020 FINAL - whitehole,
    but it didn't have PIE
*/

char buf[0x30];

void myprintf()
{
	dprintf(1,buf);
}

void vuln()
{
	while(1){
		read(0,buf,0x30);
		myprintf();
	}
}

int main()
{
	vuln();
	return 0;
}

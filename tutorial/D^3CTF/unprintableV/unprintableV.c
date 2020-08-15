//gcc -z noexecstack -fno-stack-protector -fPIE -pie  -z now  b.c -g -o printf_test
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <linux/filter.h>
#include <fcntl.h>
char buf[300];
int time=100;
int _bool=0;
void Sandbox_Loading()
{
	prctl(PR_SET_NO_NEW_PRIVS,1,0,0,0);
	struct sock_filter sfi[] = {
		{0x20,0x00,0x00,0x00000004},
		{0x15,0x00,0x05,0xc000003e},
		{0x20,0x00,0x00,0x00000000},
		{0x35,0x00,0x01,0x40000000},
		{0x15,0x00,0x02,0xffffffff},
		{0x15,0x01,0x00,0x0000003b},
		{0x06,0x00,0x00,0x7fff0000},
		{0x06,0x00,0x00,0x00000000},
	};
	struct sock_fprog sfp = {8,sfi};
	prctl(PR_SET_SECCOMP,2,&sfp);
}
void vuln()
{
	read(0,buf,300);
	printf(buf);
	time--;	
}
void init()
{
	setvbuf(stdout,0LL,2,0LL);
	setvbuf(stdin,0LL,1,0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
	alarm(0x3c);
}
void menu()
{
	char *a=buf;
	puts("welcome to d^3CTF!");
	printf("here is my gift: %p\n",&a);
	puts("may you enjoy my printf test!");
	close(1);
	while(strncmp(buf,"d^3CTF",6)&&time)
		vuln();
}
int main(int argc,char **argv)
{
	init();
	Sandbox_Loading();
	menu();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#define TIMEOUT 60

/*
 * This challenge is designed by Angelboy
 */

void handler(int signum)
{
    puts("Timeout");
    _exit(1);
}

void init()
{
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
    signal(SIGALRM, handler);
    alarm(TIMEOUT);
}

long long read_long()
{
    char buf[24];
    long long choice;
    __read_chk(0, buf, 23, 24);
    choice = atoll(buf);
    return choice;
}

void read_input(char *buf, unsigned int size)
{
    int ret;
    ret = __read_chk(0, buf, size, size);
    if (ret <= 0) {
        puts("read error");
        _exit(1);
    }
    if (buf[ret-1] == '\n') {
        buf[ret-1] = '\x00';
    }
}

void menu()
{
    puts("$$$$$$$$$$$$$$$$$$$$");
    puts("     Seethefile     ");
    puts("$$$$$$$$$$$$$$$$$$$$");
    puts(" 1. Open            ");
    puts(" 2. Read            ");
    puts(" 3. Write           ");
    puts(" 4. Exit            ");
    puts("$$$$$$$$$$$$$$$$$$$$");
    printf("Your choice :");
}

struct data {
    char buf[0x100];
    FILE *fp;
} d;

char content[0x100];
void openfile()
{
    char filename[0x30];
    memset(filename, 0, 0x30);
    if (d.fp) {
        puts("No no ! You can not open again !");
    } else {
        printf("Filename:");
        read_input(filename, 0x2f);
        if (strstr(filename, "flag")) {
            puts("No ! ");
            exit(0);
        }
        d.fp = fopen(filename, "r");
        if (d.fp)
            puts("Good ");
        else
            puts("Bad :(");
    }
}

void readfile()
{
    if (d.fp) {
        fread(content, 0x100, 1, d.fp); // fread ?
        puts("Done !");
    } else {
        puts("You need to open file first !");
    }
}

void writefile()
{
    if (strstr(content, "flag")) {
        puts("danger !");
        exit(0);
    }
    printf("Data:%s\n", content);
}

int main()
{
    init();
    while (1) {
        menu();
        switch (read_long()) {
            case 1:
                openfile();
                break;
            case 2:
                readfile();
                break;
            case 3:
                writefile();
                break;
            case 4:
                printf("Leave your name :");
                gets(d.buf);
                puts("Bye !");
                if (d.fp)
                    fclose(d.fp);
                exit(0);
                break;
            default:
                puts("Invalid choice");
                break;
        }
    }
    return 0;
}





























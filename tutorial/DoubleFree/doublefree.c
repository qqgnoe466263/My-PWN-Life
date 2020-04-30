#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#define TIMEOUT 60
#define MAX 10

struct entry {
    char *ptr;
    int size;
};

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
    puts("$$$$$$$$$$$$$$$$$$$$$");
    puts("     Double Free     ");
    puts("$$$$$$$$$$$$$$$$$$$$$");
    puts(" 1. Malloc           ");
    puts(" 2. Free             ");
    puts(" 3. Show             ");
    puts(" 4. Exit             ");
    puts("$$$$$$$$$$$$$$$$$$$$$");
    printf("Your choice :");
}

struct entry e[MAX];

void alloc()
{
    printf("Index :");
    int i = read_long();
    if (i < 0 || i > MAX) {
        puts("wrong entry !");
        return;
    }
    printf("Size :");
    int size = read_long();
    e[i].ptr = malloc(size);
    e[i].size = size;
    printf("Data :");
    read_input(e[i].ptr, size);
}

void delete()
{
    printf("Index :");
    int i = read_long();
    if (i < 0 || i > MAX) {
        puts("wrong entry !");
        return;
    }
    free(e[i].ptr);
}

void show()
{
    printf("Index :");
    int i = read_long();
    if (i < 0 || i > MAX) {
        puts("wrong entry !");
        return;
    }
    printf("%s\n", e[i].ptr);
}

int main()
{
    init();
    while (1) {
        menu();
        switch (read_long()) {
            case 1:
                alloc();
                break;
            case 2:
                delete();
                break;
            case 3:
                show();
                break;
            case 4:
                exit(0);
                break;
            default:
                puts("Invalid choice");
                break;
        }
    }
    return 0;
}





























#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct note {
    char ch1[0x8];
    char ch2[0x38];
};


int read_int()
{
    char buf[0x8];
    read(0, buf, 0x7);
    return atoi(buf);
}

int w(struct note *n, int size)
{
    char *buf;
    puts("Which chap you want to write?");
    printf("> ");
    int choice = read_int();
    
    if (choice == 1) {
        buf = n->ch1;
    } else if (choice == 2) {
        buf = n->ch2;
    } else {
        _exit(1);
    }
    printf("> "); 

    read(0, buf, size);
    int len = strlen(buf);
    if (len >= size) {
        puts("[FATAL] Buffer Overflow");
        _exit(1);
    }
    
    return len;
}

void r(struct note *n)
{
    char *buf;
    puts("Which chap you want to read?");
    printf("> ");
    int choice = read_int();
    
    if (choice == 1) {
        buf = n->ch1;
    } else if (choice == 2) {
        buf = n->ch2;
    } else {
        _exit(1);
    }

    printf("%s \n", buf);
}

void menu()
{
    puts("*****    Note    *****");
    puts("*     1. Write       *");
    puts("*     2. Read        *");
    puts("**********************");
    printf("> ");
}


int main(void) 
{
    struct note buf;
    for (int i = 0; i < 5; i++) {
    //while (1) {
        menu();
        switch (read_int()) {
            case 1:
                w(&buf, 0x58);
                break;
            case 2:
                r(&buf);
                break;
            default:
                _exit(0);
        }
    }
 
    return 0;
}

__attribute__((constructor)) void setup(void)    
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    //alarm(60);
}


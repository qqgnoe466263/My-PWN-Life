#include <stdio.h>
#include <stdlib.h>

void init_proc(){
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

void gets_and_exec(int buf_len, int (*callback)(char *)) {
    char buf[buf_len];
    printf("> ");
    gets(buf);
    callback(buf);
}

int main(int argc, char *argv[]) {
    init_proc();
    printf("Here is a present for you <3\n");
    printf("system(): %p\n", system);
    gets_and_exec(0x10, puts);
    return 0;
}

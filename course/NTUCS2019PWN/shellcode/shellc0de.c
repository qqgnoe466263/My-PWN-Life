#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


void init(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}


int main(){

    init();

    char shellcode[0x100];
    memset( shellcode , 0xcc , sizeof(shellcode) );

    puts( "shellcode >" );
    read( 0 , shellcode , 0x100 );

    for( int i = 0 ; i < 0x100 ; ++i ){
        if( shellcode[i] == '\x00' || shellcode[i] == '\x05' || shellcode[i] == '\x0f' ){
            puts( "Oops" );
            _exit(-1);
        }
    }

    void (*hello)() = shellcode;

    hello();

    return 0;
}

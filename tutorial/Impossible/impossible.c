#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>


void init(){
    setvbuf(stdout,0,2,0);
    setvbuf(stdin,0,2,0);
    setvbuf(stderr,0,2,0);
}


int main(){

    init();

    char buf[0x100];
    int len = 0;

    printf( "Size: " );
    scanf( "%d" , &len );
    
    if( len < 0 ){
        len = abs( len );
        puts( "Bad hacker :(" );
    }

    if( len > 0x100 ){
        len = 0x100;
        puts( "Too long!" );
    }

    puts( "It's safe now :)" );
    read( 0 , buf , len );

    
    return 0;
}
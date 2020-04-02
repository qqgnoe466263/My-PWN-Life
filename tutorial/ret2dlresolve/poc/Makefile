all: ret2dlresolve.c
	gcc -no-pie -fno-stack-protector ret2dlresolve.c -o ret2dlresolve -Wl,-dynamic-linker /home/ghost/CTF/glibc/glibc-2.27/64/lib/ld-2.27.so -g 

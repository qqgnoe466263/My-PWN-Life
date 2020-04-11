all: no partial full

no1: src.c
	gcc src.c -o no -no-pie -fno-stack-protector -Wl,-z,norelro -m32
partial: src.c
	gcc src.c -o partial -no-pie -fno-stack-protector -m32

full: src.c
	gcc src.c -o full -no-pie -fno-stack-protector -Wl,-z,relro,-z,now -m32

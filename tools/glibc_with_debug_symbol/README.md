# 編譯glibc帶Debug symbol


先到glibc官網載所需的版本(我用的是glibc-2.23.tar.gz)

    http://ftp.gnu.org/gnu/glibc/

解壓縮

    $ tar -xvf glibc-2.23.tar.gz

然後看是需要 32bits 還是 64 bits

32bits:

    $ cd glibc-2.23
    $ mkdir build32 ; cd build32
    $ CC="gcc -m32" CFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error" CXXFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error" ../configure --prefix=/<your_path>/glibc-2.23/32 --host=i686-linux-gnu

可能需要安裝:
    $ sudo apt-get install gcc-multilib gawk bison -y

64bits:

    $ cd glibc-2.23
    $ mkdir build64 ; cd build64
    $ CFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error" CXXFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error" ../configure --prefix=/<your_path>/glibc-2.23/64

直接patch binary更換glibc(64bits為例)
    
    $ sudo ln -s <your_path>/glibc-2.29/64/lib/ld-2.29.so /lib64/Ld-linux-x86-64.so.2
    $ vim <binary> , 把ld-linux-x86-64.so.2改成Ld-linux-x86-64.so.2
        /lib64/Ld-linux-x86-64.so.2 => /lib64/ld-linux-x86-64.so.2 (0x00007f3fbbacc000)
    $ ls -al /lib64/Ld-linux-x86-64.so.2
        lrwxrwxrwx 1 root root 50  七  26 23:50 /lib64/Ld-linux-x86-64.so.2 -> <your_path>/glibc-2.29/64/lib/ld-2.29.so
    
**Note:ubuntu20.04(glibc2.31 64bits)**
    
    $ CFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error -Wno-maybe-uninitialized -Wno-unused-result" CXXFLAGS="-g -g3 -ggdb -gdwarf-4 -Og -Wno-error -Wno-maybe-uninitialized -Wno-unused-result" ../configure --prefix=/<your_path>/glibc-2.31/64

**Note:記得上述要去更改你的路徑**

再來編譯&安裝
    
    $ make -j8 ; make install

大功告成,這樣就有了**帶Debug symbol的glibc**了


最後在編譯你要的檔案的時候如下使用,就可以在gdb裡面看到source了

    $ gcc -m32 test.c -o test -Wl,-dynamic-linker /<your_path>/glibc-2.23/32/lib/ld-2.23.so -g 
    
## Note

* Compiling 2.23 2.27 2.29 at ubuntu18.04 worked
* Compiling 2.31 at ubuntu20.04 worked

## Reference
    
* [筆記sean大大的上課內容](https://www.youtube.com/watch?v=wsIvqd9YqTI)
* https://qianfei11.github.io/2019/03/04/Ubuntu16-04下编译libc2-23/

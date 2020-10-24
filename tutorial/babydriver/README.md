# babydriver
> 記錄一下有關kernel pwn的分析方式

* 解壓縮得到 :
    * boot.sh : 啟動題目(kernel)的腳本，通常是用QEMU模擬
    * bzImage : kernel的映像檔(Image file)
    * rootfs.cpio : 打包好的文件系統(file system)

* 先把**rootfs.cpio**解開
    
    $ mkdir fs
    
    $ cd fs
    
    $ cp ../rootfs.cpio .
    
    $ cpio -idmv < rootfs.cpio

* 在**init**中會發現，有漏洞的驅動，直接把它拖進IDA就可以分析了

    insmod /lib/modules/4.4.72/babydriver.ko

* 如果要動態分析的話，要先從**bzImage**取出**vmlinux**，

   $ /usr/src/linux-headers-$(uname -r)/scripts/extract-vmlinux bzImage > vmlinux

* 然後就是在**boot.sh**的QEMU加入**remote debug**的參數(預設port為1234)

    ... -s -S

* 就可以使用**gdb**去做分析了

    $ ./gdb vmlinux
    (gdb) target remote localhost:1234
    (gdb) c

* 從QEMU中我們可以得到babydriver.ko的**.text**位置

    $ cat /sys/module/babydriver/sections/.text
    0xffffffffc0000000

* 回到gdb中加入這個**symbol**

    (gdb) add-symbol-file babydriver.ko 0xffffffffc0000000

* 大功告成！可以用**gdb**去做**debug**了


### Ref

* [CISCN 2017 babydriver](https://beafb1b1.github.io/kernel/ciscn_2017_babydriver_UAF/#_3)




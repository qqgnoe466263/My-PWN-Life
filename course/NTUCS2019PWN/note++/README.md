
size = 0

malloc(size) 還是會分配最小的chunk 0x21
	
但 size -1 = 0xffffffff 又是 unsigned 達到heapoverflow任意寫

	57 read_input( notes[i].data , size - 1 );
	20 int read_input( char *buf , unsigned int size ){

利用這個漏洞,可以將某一塊chunk size 修改成 small chunk
藉此free掉這個small chunk去leak出main_arena+N的位置

再利用fastbin-attack 將chunk改到malloc_hook附近去修改malloc_hook 

駭客思維
	
	one_gadget都失效的話,double free的警告通知會呼叫malloc,或許會成功

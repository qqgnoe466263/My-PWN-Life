
# Write-Up

因為glibc版本不同，所以要先去patch一下，通常做法是把***ld***改成***LD***，然後把題目給的ld-2.29.so複製一份到lib64下，變成***/lib64/Ld-linux-x86-64.so.2***，接著用***LD_PRELOAD***就可以開始解題了。

在***printf***裡面，若給一個超大的字串(e.g. %100000c)他會去呼叫***malloc***，也會呼叫***free***，所以有FSB，可以修改***__free_hook***或者***__malloc_hook***成***one_gadget***來拿到shell。

不過卡很久的是，可能因為作業系統問題(?，踹了一堆***one_gadget***在本地跑不動，一連remote就拿到shell，orz。

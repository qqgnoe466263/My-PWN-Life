import subprocess
import re

class AutoHeap(gdb.Command):

    def __init__(self):
        super(AutoHeap,self).__init__("hh",gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        fn = gdb.execute('info proc mapping', True, True).split('\n')
        for r in fn:
            if '[heap]' in r:
                heap_base = str(r.split()[0])
                break
        
        # >glibc2.27
        # heap = str(hex(int(heap_base,16) + 0x250)) 
                
        # Example:
        # x/10gx 0x602000
        gdb.execute('x/%sgx %s' % (arg,heap_base))

AutoHeap()

import subprocess
import re


class AutoAttach(gdb.Command):
    def __init__(self):
        super(AutoAttach,self).__init__("at",gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        try:
            gdb.execute('info proc', True, True)
            gdb.execute('kill', True, True)
        except gdb.error:
            pass

        if arg:
            fn = arg
        else:
            fn = re.findall('Symbols from "(.*)"', gdb.execute('info files', True, True))
       
        ps = list(map(int, subprocess.check_output(['/bin/pidof',fn[0]]).split()))
        gdb.execute('attach %d' % ps[0])
        gdb.execute('c')


AutoAttach()

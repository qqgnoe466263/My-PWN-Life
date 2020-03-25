import subprocess
import re

class BinaryBase(gdb.Command):

	def __init__(self):
		super(BinaryBase,self).__init__("bb",gdb.COMMAND_USER)

	def invoke(self, arg, from_tty):
		fn = gdb.execute('info proc mapping', True, True).split('\n')
		binary_base = fn[4].split()[0]
		argv = arg.split()
		location = str(hex(int(binary_base,16) + int(argv[1],16)))

		# bb 10 0x20
		gdb.execute('x/%sgx %s' % (argv[0],location))

BinaryBase()

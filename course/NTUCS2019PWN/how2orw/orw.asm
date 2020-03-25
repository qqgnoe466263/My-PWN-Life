global _start

section .text
_start:
	xor rax,rax
	xor rdi,rdi
	xor rsi,rsi
	xor rdx,rdx
	
	mov rax,2
	mov rdi,file
	mov rsi,0
	syscall

	mov rdi,rax
	mov rax,0
	mov rsi,buf
	mov rdx,4
	syscall

	mov rax,1
	mov rdi,1
	mov rsi,buf
	mov rdx,5
	syscall

section .data
	file db 'flag',0
	len equ $ - file

section .bss
	buf resb 5


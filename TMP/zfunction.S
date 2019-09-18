.section	.data
.section	.text
.globl zfunction

zfunction:
	pushl %ebp
	mov %esp, %ebp
	movl 8(%esp), %ebx	#taking the value passed to the function and moving it to ebx
	and $0xFFFC01FF, %ebx #clears the bits 9-17 from the right(counting from 0)
	shr $0x8, %ebx	      #this right-shifts the register by 8bits
	OR $0xFF000000, %ebx  #converting the first 8bits into 1s
	movl %ebx, %eax		  #moving into eax register to take the return value
	pop %ebp
	ret

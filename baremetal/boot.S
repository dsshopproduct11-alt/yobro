.section .text
.code32
.global _start
.extern kernel_main
_start:
    cli
    mov $stack_top, %esp
    call kernel_main
1:  hlt
    jmp 1b
.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:

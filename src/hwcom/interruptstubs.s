.set IRQ_BASE, 0x20

.section .text

.extern _ZN5sinix5hwcom16InterruptManager15HandleInterruptEhj

.macro HandleException num
.global _ZN5sinix5hwcom16InterruptManager16HandleException\num\()Ev
_ZN5sinix5hwcom16InterruptManager16HandleException\num\()Ev:
  movb $\num, (interruptnumber)
  jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN5sinix5hwcom16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN5sinix5hwcom16InterruptManager26HandleInterruptRequest\num\()Ev:
  movb $\num + IRQ_BASE, (interruptnumber)
  jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x0C

int_bottom:
  pusha
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs

  pushl %esp
  push (interruptnumber)
  call _ZN5sinix5hwcom16InterruptManager15HandleInterruptEhj
  add %esp, 6
  mov %eax, %esp

  pop %gs
  pop %fs
  pop %es
  pop %ds
  popa

.global _ZN5sinix5hwcom16InterruptManager22IgnoreInterruptRequestEv
_ZN5sinix5hwcom16InterruptManager22IgnoreInterruptRequestEv:

  iret
  
.data
  interruptnumber: .byte 0 

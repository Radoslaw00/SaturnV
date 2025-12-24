section .text
global _start   ; entry point

_start:
.loop:
    ; call functions here
    ; call my function

    jmp .loop     ; infinite loop

; exit (never reached in this infinite loop)
mov eax, 1        ; sys_exit
mov ebx, 0        ; return code 0
int 0x80

@WINDOWS NT 10.0
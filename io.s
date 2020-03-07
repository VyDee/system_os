extern interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push	dword 0                     ; push 0 as error code
	push	dword %1                    ; push the interrupt number
	jmp	common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push    dword %1                    ; push the interrupt number
	jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

common_interrupt_handler:               ; the common parts of the generic interrupt handler
	; save the registers
	push    eax
	push    ebx
	push	ecx
	push	edx
	push	ebp
	push	esi
	push	edi

        ; call the C function
        call    interrupt_handler

        ; restore the registers
	pop	edi
	pop	esi
	pop	ebp
	pop	edx
	pop	ecx
	pop	ebx
    pop eax

	; restore the esp
	add     esp, 8

	; return to the code that got interrupted
	iret

no_error_code_interrupt_handler	33	; create handler for keyboard

global segments_load_gdt
global segments_load_registers

segments_load_gdt:
	lgdt [esp + 4]
	ret

segments_load_registers:
	mov ax, 0x10
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:flush_cs ; 0x08 - an offset into GDT for the second (kernel code segment) record. 

flush_cs:
	ret

global  load_idt

; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
;        [esp    ] the return address

load_idt:
        mov eax, [esp + 4]
        lidt [eax]
        ret


global outb             ; make the label outb visible outside this file

    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
    outb:
        mov al, [esp + 8]    ; move the data to be sent into the al register
        mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
        out dx, al           ; send the data to the I/O port
        ret                  ; return to the calling function

global inb

    ; inb - returns a byte from the given I/O port
    ; stack: [esp + 4] The address of the I/O port
    ;        [esp    ] The return address
    inb:
        mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
        in  al, dx              ; read a byte from the I/O port and store it in the al register
        ret                     ; return the read byte
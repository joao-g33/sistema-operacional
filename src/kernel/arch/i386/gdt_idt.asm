; créditos: https://github.com/fleakos/Fleak

global gdt_set
global idt_set

gdt_set:
	mov eax, [esp+4] ; ponteiro da GDT passado como argumento  
	lgdt [eax]       ; carregar ponteiro da GDT
	
	; segmento de dados: offset 0x10 
	mov ax, 0x10
	; Setting up all the data Segments 
	mov ds, ax 
	mov fs, ax 
	mov es, ax 
	mov gs, ax 
	mov ss, ax 
	
	; segmento de código do kernel (CS, ou kernel code segment): offset 0x08 (efetuar far jmp)
	jmp 0x08:.flush 
	
    .flush:
    	ret


idt_set:
	mov eax, [esp+4] ; ponteiro da IDT passado como argumento 
	lidt [eax]       ; carregar ponteiro da IDT no registrador especial: IDTR
	ret 
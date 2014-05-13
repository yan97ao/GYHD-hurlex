[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]

	mov ax, 0x10	;offset to kernel data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush	;jump to kernel code segment

.flush:
	ret

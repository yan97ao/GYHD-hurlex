#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	console_write_color("Hello, OS Kernel!\n", rc_black, rc_green);

	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

	return 0;
}

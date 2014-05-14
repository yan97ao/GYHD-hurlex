#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	console_write_color("Hello, OS Kernel!\n", rc_black, rc_green);

	init_timer(200);

	asm volatile("sti");
	return 0;
}

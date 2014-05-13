#include "gdt.h"
#include "console.h"
#include "debug.h"

int kern_entry()
{
	init_debug();
	init_gdt();

	console_clear();
	console_write_color("Hello, OS Kernel!\n", rc_black, rc_green);
	return 0;
}

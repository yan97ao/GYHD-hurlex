#include "console.h"
#include "debug.h"

int kern_entry()
{
	init_debug();
	console_clear();
	console_write_color("Hello, OS Kernel!\n", rc_black, rc_green);
	painc("test");
	return 0;
}

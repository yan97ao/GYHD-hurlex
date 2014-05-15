#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include <pmm.h>

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	console_write_color("Hello, OS Kernel!\n", rc_black, rc_green);

	init_timer(200);

	/*asm volatile("sti");*/

	printk("Kernel in memory start: 0x%08X\n", kern_start);
	printk("Kernel in memory end: 0x%08X\n", kern_end);
	printk("Kernel in memory used: %d KB \n\n", (kern_end - kern_start) / 1024);

	show_memory_map();

	return 0;
}

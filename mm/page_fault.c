#include "vmm.h"
#include "debug.h"

void page_fault(pt_regs *regs)
{
	uint32_t cr2;
	asm volatile("mov %%cr2,%0":"=r"(cr2));

	printk("Page fault at 0x%x, virtual fault address 0x%x\n",regs->eip,cr2);
	printk("Error code %x\n",regs->err_code);

	if( !(regs->err_code & 0x1)) {
		printk(rc_black,rc_red,"Page wasn't present.\n");
	}

	if(regs->err_code & 0x2) {
		printk(rc_black,rc_red,"Write error.\n");
	} else {
		printk(rc_black,rc_red,"Read error.\n");
	}

	if(regs->err_code & 0x4) {
		printk(rc_black,rc_red,"In user mode.\n");
	} else {
		printk(rc_black,rc_red,"In kernel mode.\n");
	}

	if(regs->err_code & 0x8) {
		printk(rc_black,rc_red,"Reserved bits being overwritten.\n");
	}

	if(regs->err_code & 0x10) {
		printk(rc_black,rc_red,"Error during an instruction fetch.\n");
	}
}

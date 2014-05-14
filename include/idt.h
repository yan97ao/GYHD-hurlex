#ifndef _INCLUDE_IDT_H_
#define _INCLUDE_IDT_H_

#include"types.h"

void init_idt();

typedef struct idt_entry_t {
	uint16_t base_lo;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

typedef struct pt_regs_t {
	uint32_t ds;
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t int_no;
	uint32_t err_code;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
} pt_regs;

typedef void (*interrupt_handler_t)(pt_regs *);

void register_interrupt_handler(uint8_t n, interrupt_handler_t h);

void isr_handler(pt_regs *regs);

void isr0();	//DE
void isr1();	//DB
void isr2();	//NMI
void isr3();	//BP
void isr4();	//OF
void isr5();	//BR
void isr6();	//UD
void isr7();	//NM
void isr8();	//DF
void isr9();	//
void isr10();	//TS
void isr11();	//NP
void isr12();	//SS
void isr13();	//GP
void isr14();	//PF
void isr15();	//cpu reserved
void isr16();	//MF
void isr17();	//AC
void isr18();	//MC
void isr19();	//XM

//20 ~ 31 intel reserved
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void isr255();

void irq_handler(pt_regs *regs);

#define IRQ0	32
#define IRQ1	33
#define IRQ2	34
#define IRQ3	35
#define IRQ4	36
#define IRQ5	37
#define IRQ6	38
#define IRQ7	39
#define IRQ8	40
#define IRQ9	41
#define IRQ10	42
#define IRQ11	43
#define IRQ12	44
#define IRQ13	45
#define IRQ14	46
#define IRQ15	47

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();


#endif /* end of include guard */

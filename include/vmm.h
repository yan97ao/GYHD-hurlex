#ifndef _INCLUDE_VMM_H_
#define _INCLUDE_VMM_H_

#include "types.h"
#include "idt.h"

#define PAGE_OFFSET		0xC0000000

#define PAGE_PRESENT	1<<0
#define PAGE_WRITE		1<<1
#define PAGE_USER		1<<2

#define PAGE_SIZE		4096
#define PAGE_MASK		0xFFFFF000

#define PGD_INDEX(x)	(((x) >> 22) & 0x3FF)
#define PTE_INDEX(x)	(((x) >> 12) & 0x3FF)
#define OFFSET_INDEX(x)	((x) & 0xFFF)

typedef uint32_t pgd_t;

typedef uint32_t pte_t;

#define PGD_SIZE (PAGE_SIZE/sizeof(pte_t))

#define PTE_SIZE (PAGE_SIZE/sizeof(uint32_t))

#define PTE_COUNT 128

extern pgd_t pgd_kern[PGD_SIZE];

void init_vmm();

void switch_pgd(uint32_t pd);

void map(pgd_t *pgd_now, uint32_t va, uint32_t pa, uint32_t flags);

void unmap(pgd_t *pgd_now, uint32_t va);

uint32_t get_mapping(pgd_t *pgd_now, uint32_t va, uint32_t *pa);

void page_fault(pt_regs *regs);

#endif /* end of include guard */

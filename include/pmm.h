#ifndef _INCLUDE_PMM_H_
#define _INCLUDE_PMM_H_

#include "multiboot.h"

extern uint8_t kern_start[]; 
extern uint8_t kern_end[];

void show_memory_map();

#endif /* end of include guard */

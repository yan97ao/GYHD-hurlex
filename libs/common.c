#include "common.h"

inline void outb(uint16_t port,uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

// 开启中断
inline void enable_intr()
{
    asm volatile ("sti");
}

// 关闭中断
inline void disable_intr()
{
    asm volatile ("cli" ::: "memory");
}

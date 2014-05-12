#include "common.h"
#include "console.h"

static uint16_t *video_memory = (uint16_t *)0xB8000;

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void move_cursor()
{
	uint16_t cursorLocation = cursor_y * 80 + cursor_x;

	outb(0x3D4, 14);
	outb(0x3D5, cursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLocation);
}

void console_clear()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);

	int i;
	for (i = 0; i < 80 * 25; i++) {
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

static void scroll()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);
	
	if(cursor_y >= 25) {
		int i;

		for (i = 0; i < 24 * 80; i++) {
			video_memory[i] = video_memory[i+80];
		}

		for (i = 24 * 80; i < 25 * 80; i++) {
			video_memory[i] = blank;
		}
		
		cursor_y = 24;
	}
}

void console_putc_color(char c, real_color_t back, real_color_t fore)
{
	uint8_t back_color = (uint8_t)back;
	uint8_t fore_color = (uint8_t)fore;

	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
	uint16_t attribute = attribute_byte << 8;

	if (c == 0x08 && cursor_x) {
		cursor_x--;
	} else if (c == '\r') {
		cursor_x = 0;
	} else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') {
		video_memory[cursor_y*80 + cursor_x] = c | attribute;
		cursor_x++;
	}

	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}

	scroll();

	move_cursor();
}

void console_write(char *cstr)
{
	while(*cstr) {
		console_putc_color(*cstr++, rc_black, rc_white);
	}
}

void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
	while(*cstr) {
		console_putc_color(*cstr++, back, fore);
	}
}

void console_write_hex(uint32_t n, real_color_t back, real_color_t fore)
{
	console_write_color("0x",back,fore);
	char charlist[] = "0123456789ABCDEF";
	int c[8];

	c[0] = (n & 0xF0000000) >> 28; 
	c[1] = (n & 0x0F000000) >> 24; 
	c[2] = (n & 0x00F00000) >> 20; 
	c[3] = (n & 0x000F0000) >> 16; 
	c[4] = (n & 0x0000F000) >> 12; 
	c[5] = (n & 0x00000F00) >> 8; 
	c[6] = (n & 0x000000F0) >> 4; 
	c[7] = (n & 0x0000000F) >> 0;

	int i = 0;
	for (i = 0; i < 8; i++) {
		console_putc_color(charlist[c[i]], back, fore);
	}
}

void console_write_dec(int32_t n, real_color_t back, real_color_t fore)
{
	char charlist[] = "0123456789";
	if(n < 0) {
		console_putc_color('-', back, fore);
		n = -n;
	}

	int i = 0;
	char c1[256];
	while(n > 0) {
		c1[i] = charlist[n % 10];
		n = n/10;
		i++;
	}
	
	int j = 0;
	char c2[256];
	c2[i--] = '\0';
	while(i >= 0) {
		c2[i--] = c1[j++];
	}

	console_write_color(c2, back, fore);	
}


#include "string.h"

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
	while(len--) {
		*dest++ = *src++;
	}
}

void memset(void *dest, uint8_t val, uint32_t len)
{
	unsigned char *dst = (unsigned char*)dest;

	while(len--) {
		*dst++ = val;
	}
}

void bzero(void *dest, uint32_t len)
{
	memset(dest, 0, len);
}

int strcmp(const char *str1, const char *str2)
{
	while(*str1 && (*str1 == *str2)) {
		*str1++;
		*str2++;
	}
	return *str1-*str2;
}

char *strcpy(char *dest, const char *src)
{
	char *ret = dest;
	while( *dest++ = *src++);
	return ret;
}

char *strcat(char *dest, const char *src)
{
	char *ep = dest;
	while(*ep)ep++;

	while(*ep++ = *src++);

	return dest;
}

int strlen(const char *src)
{
	int len = 0;
	while(*src++) len++;
	return len;
}


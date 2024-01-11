#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void note(const char *fmt, ...) {
	printf("\033[0;33m[+] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
}

void warn(const char *fmt, ...) {
	printf("\033[0;31m[!] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
	
}

void info(const char *fmt, ...) {
	printf("\033[47;30m[i] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
	
}


void write_line(const char *fmt, ...) {
	printf("\033[0;32m[?] ");
	va_list args;
    	va_start(args, fmt);
    	vprintf(fmt, args);
    	va_end(args);
	printf("\033[0m");
	for(int i = 0; i < 100; i++)
		printf("\b");
}

void die(const char *fmt) {
	perror(fmt);
	exit(1);
}


void hexdump(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}




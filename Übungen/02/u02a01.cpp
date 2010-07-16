#include <stdio.h>

int main() {
	// Datentyp short -> Größe 16 Bit
	signed short a = -32767;
	unsigned short b = a;
	printf("b = %d \n", b);
	
	unsigned short k = 1;
	if( k>>1 )
		printf("k = %d \n", k);
	
	float f;
	f = 1/2;
	printf("f = %.2f \n", f);
	
	char c = 'a', d = c++, e = ++c;
	printf("d = %c e = %c \n", d, e);
	
	return 0;
}

/*
Prognose:
b = 0
f = 0.00
d = a e = c
*/

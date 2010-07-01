#include <stdio.h>


typedef char string[101];

int main() {
	string s1, s2;
	const char* c = "sdf";
	const char* d = "ghj";
//	printf("%c\n", *c);
//	c++;
//	printf("%c\n", *c);
//	c++;
//	printf("%c\n", *c);
//	c++;
//	printf("%c\n", *c);
	char a = 'a';
	while( a == "\0" ) {
		char a = *c;
		//printf("%i\n", c);
		printf("%i\n", a);
		printf("%i\n", c);
		c++;
	}
	//s1 = "sdf";
	
	//s2 = "sdfw";
	return 0;
}

#include <stdio.h>

void foobar() {
	unsigned char c;
	scanf("%c", &c);
	if(c != '#')
		foobar();
	printf("%c", c);
};

int main() {
	foobar();
	return 0;
}

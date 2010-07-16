#include <stdio.h>

int main() {
	/* Umformulieren in while-Schleife
	unsigned int i, fak = 1, n;
	scanf("%u", &n);
	for( i = 2; i <= n; i = i + 1 )
		fak = fak * i;	
	*/
	unsigned int i = 2, fak = 1, n;
	scanf("%u", &n);
	
	while( i <= n ) {
		fak = fak * i;
		i++;
	}

	return 0;
}

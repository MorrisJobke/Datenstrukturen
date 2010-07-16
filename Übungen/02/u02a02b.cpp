#include <stdio.h>

int main() {
	/* Umformulieren in for-Schleife
	int i, sum = 0;
	do {
		scanf("%d", &i);
		sum = sum + i;
	} while(i != 0)
	*/
	
	int i, sum = 0;
	
	for(scanf("%d", &i);i != 0;scanf("%d", &i)) {
		sum = sum + i;	
	}
	return 0;
}

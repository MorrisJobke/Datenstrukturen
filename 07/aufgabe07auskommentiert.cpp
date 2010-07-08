//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>

// Grenze N der zu sortierenden Zahlen und des Feldes
const int N = 10;

// Sortierfunktion
int* mysort( int* a ) {
	// Feld mit der Anzahl der einzelnen Zahlen
	int b[N] = { 0 };
	
	// 1. Durchlauf des zu sortierenden Feldes und die Ermittlung der Anzahl der
	// einzelnen Zahlen
	for( int i = 0; i < N; i++ ) {
		b[a[i]-1]++;
	}
	
	// Neuschreiben des Feldes mit den Werten aus dem temporären Feld b
	int c = 0;
	for( int i = 0; i < N; i++ ) {
		for( int j = 0; j < b[i]; j++ ) {
			a[c] = i+1;
			c++;
		}
		if( c == N )
			break;
	}
	return a;
};

int main(){	
	int unsorted[] = {6, 6, 5, 10, 2, 3, 2, 4, 6, 1};
	
//	srand(time(NULL));
//	for( int i = 0; i < N; i++ ) {
//		unsorted[i] = rand()%N + 1;
//		printf("%3i ", unsorted[i]);
//	}
//	printf("\n");
	int* sorted = mysort(unsorted);
//	for( int i = 0; i < N; i++ ) {
//		printf("%3i ", sorted[i]);
//	}
//	printf("\n");
	return 0;
}

//#include <stdio.h>

const int N = 12;

int* mergesort( int* data, int length ) {
	int middle = length / 2;
	
	if( length > 1 ) {
		// rekursives Aufrufen - vom ersten Element bis zur Mitte
		// linkes Teilfeld
		mergesort(&data[0], middle);			
		// rekursives Aufrufen - vom mittleren Element bis zum letzten
		// rechtes Teilfeld
		mergesort(&data[middle], length - middle);
	}
	
	// Feld ist bereits sortiert, wenn es nur ein Element hat
	if( length == 1 )
		return data;
	
	int tmp[N];	
	int a = 0;				// Index des temporären Feldes
	int b = 0;				// Index des linken Feldes
	int c = middle;			// Index des rechten Feldes
	
	// solange im linken und im rechten Teilfeld noch Elemente sind
	while(b < middle and c < length){
		if( data[b] < data[c] )
			tmp[a++] = data[b++];		// linkes Element kleiner
		else
			tmp[a++] = data[c++];		// rechtes Element kleiner
	}
	
	// Rest des linken Teilfeldes noch übertragen
	while( b < middle )
		tmp[a++] = data[b++];
		
	// Rest des rechten Teilfeldes noch übertragen
	while( c < length ) 
		tmp[a++] = data[c++];
	
	// sortierte Elemente zurückkopieren
	for( int i = 0; i < length; i++ )
		data[i] = tmp[i];
	
	return data;
};

int main(){	
	int unsorted[] = {6, 46, 5, 10, 23, 83, 82, 54, 16, 23, 482, 24};
			
//	for( int i = 0; i < N; i++ ) {
//		printf("%3i ", unsorted[i]);
//	}
//	printf("\n");
	
	int* sorted = mergesort(unsorted, N);
	
//	for( int i = 0; i < N; i++ ) {
//		printf("%3i ", sorted[i]);
//	}
//	printf("\n");
	
	return 0;
}

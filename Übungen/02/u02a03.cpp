#include <stdio.h>

const int N = 10;
typedef int array[N];

void minmax( array data, int &min, int &max ) {
	min = max = data[0];
	for( int i = 1; i < N; i++ ) {
		if( min > data[i] )
			min = data[i];
		if( max < data[i] )
			max = data[i];
	}
};

int main() {
	array a = { 14, 123, 23, 25, 57, 34, 93, 29, 84, 45 };
	int min, max;
	minmax( a, min, max );
	return 0;
}

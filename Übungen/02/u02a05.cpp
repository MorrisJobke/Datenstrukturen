#include <stdio.h>

float average( float* a, int s ) {
	float sum = 0.0;
	int i = s - 1;
	while(i--){
		sum += *a;
		a++;
	}
	return sum/s;
}; 

int main() {
	const int FSize = 5;
	float array[FSize] = {4.0, 5.0, 3.0, 4.0, 2.0};
	printf("%.5f\n", average(array, FSize));

}


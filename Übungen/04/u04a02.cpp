#include <stdio.h>

class rationalNumber {
private:
	int numerator;
	int denominator;
public:
	rationalNumber(int n, int d) {
		numerator = n;
		if( d != 0)
			denominator = d;
		else
			printf("denominator is zero\n");
	};
};

int main() {
	
	return 0;
}

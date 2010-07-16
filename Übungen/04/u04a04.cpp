#include <stdio.h>

class vektor {
private:
	int x, y, z;
public:
	int getX() {
		return x;
	};
	
	int getY() {
		return y;
	};
	
	int getZ() {
		return z;
	};

	vektor(int a, int b, int c) {
		x = a;
		y = b;
		z = c;
	};
	
	vektor* add(vektor* v) {
		vektor* tmp = new vektor(
			x + v->getX(), 
			y + v->getY(), 
			z + v->getZ()
		);
		return tmp;
	};
	
	int skalar(vektor* v) {
		return x * v->getX() + y * v->getY() + z * v->getZ();
	};
	
	vektor* kreuz(vektor* v) {
		vektor* tmp = new vektor(
			y * v->getZ() - z * v->getY(), 
			z * v->getX() - x * v->getZ(), 
			x * v->getY() - y * v->getX()
		);
		return tmp;		
	};
	
	bool ortho(vektor* v) {
		if(skalar(v) == 0)
			return true;
		return false;
	};
	
	bool linear(vektor* v) {
//		printf("%f\n", x/float(v->getX()));
//		printf("%f\n", y/float(v->getY()));
//		printf("%f\n", z/float(v->getZ()));
		if(
			x/float(v->getX()) == y/float(v->getY()) and 
			x/float(v->getX()) == z/float(v->getZ())
		)
			return true;
		return false;
	};
	
	void print() {
		printf("( %i, %i, %i )\n", x, y, z);
	};

};

int main() {	
	vektor* v1 = new vektor(2, 4, 2);
	vektor* v2 = new vektor(3, 6, 3);
	v1->print();
	v2->print();
	v1->add(v2)->print();
	printf("%i\n", v1->skalar(v2));
	v1->kreuz(v2)->print();	
	printf("%i\n", v1->ortho(v2));
	printf("%i\n", v1->linear(v2));
	return 0;
}

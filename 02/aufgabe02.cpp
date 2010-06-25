#include <stdio.h>


class intList {
	private:		
		static const int N = 100;
		
		struct intElem {
			int info;
			intElem *pred, *succ;
		};	
		
		intElem elements[N];
		bool memory[N];
	
	public:
		intList() {
			int i;
			for( i = 0; i < N; i++ ) {
				this->memory[i] = false;
			}
		}
	
		intElem* request() {
			int i;
			for( i = 0; i < N; i++ ) {
				if( this->memory[i] == false ) {
					this->memory[i] = true;
					return &(this->elements[i]);
				}
			}
			return NULL;
		}
	
		void free(intElem* el) {
			int i;
			for( i = 0; i < N; i++ ) {
				if( &(this->elements[i]) == el ) {
					this->memory[i] = false;
					break;
				}
			}
		}
	
		void insertSorted(int z) {
			intElem* tmp;
			tmp = this->request();
			if( tmp != NULL ) {
				tmp->info = z;
			}		
		}
	
		intElem* exists(int z) {
			int i;
			for( i = 0; i < N; i++ ) {
				if( this->memory[i] == true and 
					this->elements[i].info == z ) {
					return &(this->elements[i]);
				}
			}
			return NULL;		
		}
	
		void remove(int z) {	
			intElem* tmp;
			tmp = this->exists(z);
			if( tmp != NULL ) {
				this->free(tmp);
			}
		}
		
		void print() {
			int i;
			for( i = 0; i < N; i++ ) {
				if( this->memory[i] == true ) {
					printf("%3i", this->elements[i].info);
				} else {
					printf("%3s", "#");
				}
				if( (i+1)%10 == 0 ){
					printf("\n");
				}
			}
		}
};

int main(){
	intList m;
	int i;
	for( i=2; i <= 50; i++) {
		m.insertSorted(i);
	}
	m.print();
	printf("remove mod 2\n");
	for( i=2; i <= 50; i++) {
		if( i%2 == 0 ) {
			m.remove(i);
		}
	}
	m.print();
	printf("remove mod 3\n");
	for( i=2; i <= 50; i++) {
		if( i%3 == 0 ) {
			m.remove(i);
		}
	}
	m.print();
	printf("remove mod 5\n");
	for( i=2; i <= 50; i++) {
		if( i%5 == 0 ) {
			m.remove(i);
		}
	}
	m.print();	
}

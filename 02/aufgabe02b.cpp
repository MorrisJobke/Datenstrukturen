#include <stdio.h>

struct intElem{
	int info;
	intElem *pred, *succ;
};

class intList {
protected:
	static const int N = 1000;
	intElem* memory[N];
public:
	intElem* request() {
		for( int i = 0; i < N; i++ ) {
			if( this->memory[i] == NULL ){
				intElem* tmp = new intElem;
				this->memory[i] = tmp;
				return tmp;
			}
		}
		return NULL;
	};
	
	void free( intElem* el) {
		for( int i = 0; i < N; i++ ) {
			if( this->memory[i] == el ){
				this->memory[i] = NULL;
				break;
			}				
		}
		delete el;		
	};
	
	intElem* insertSorted( intElem* head, int z ) {
		intElem* insert;
		insert = this->request();
		if( insert == NULL )
			return NULL;
		else {
			insert->pred = NULL;
			insert->succ = NULL;
			insert->info = z;
		}
		if( head == NULL )
			return insert;
		intElem* tmp = head;
		while( true ) {
			if( tmp->info >= z ) {
				if( tmp == head ) {
					insert->succ = head;
					insert->succ->pred = insert;
					return insert;
				}
				insert->pred = tmp->pred;
				insert->succ = tmp;
				insert->pred->succ = insert;
				insert->succ->pred = insert;
				return head;
			}
			if( tmp->succ == NULL )
				break;
			tmp = tmp->succ;
		}
		insert->pred = tmp;
		insert->pred->succ = insert;
		return head;
	};
	
	bool exists( intElem* head, int z ) {
		while( head != NULL ) {
			if( head->info == z )
				return true;
			head = head->succ;
		}
		return false;
	};
	
	intElem* remove( intElem* head, int z ) {
		intElem* tmp = head;
		while( tmp != NULL ) {
			if( tmp->info == z ){
				// head of list
				if( tmp->pred == NULL ) {
					head = tmp->succ;
					head->pred = NULL;
				} else {
					tmp->pred->succ = tmp->succ;				
				}
				if( tmp->succ != NULL )
					tmp->succ->pred = tmp->pred;
				this->free( tmp );
			}
			tmp = tmp->succ;
		}
		return head;
	};
	
	void print( intElem* head ) {
		int i = 1;
		while( head != NULL ) {
			printf("%3i ", head->info);
			head = head->succ;
			if( i%10 == 0 )
				printf("\n");
			i++;
		}
		printf("\n");
	}
};

int main() {
	intList l;
	intElem* h = NULL;
	for( int i = 2; i <= 50; i++ ) {
		h = l.insertSorted( h, i );
	}
	l.print(h);
	printf("remove mod 2\n");
	for( int i = 2; i <= 50; i++) {
		if( i%2 == 0 ) {
			h = l.remove(h, i);
		}
	}
	l.print(h);
	printf("remove mod 3\n");
	for( int i = 2; i <= 50; i++) {
		if( i%3 == 0 ) {
			h = l.remove(h, i);
		}
	}
	l.print(h);
	printf("remove mod 5\n");
	for( int i = 2; i <= 50; i++) {
		if( i%5 == 0 ) {
			h = l.remove(h, i);
		}
	}
	l.print(h);
	// middle
	h = l.insertSorted( h, 13);
	// tail
	h = l.insertSorted( h, 132);
	// head
	h = l.insertSorted( h, 1);
	l.print(h);
	return 0;
}

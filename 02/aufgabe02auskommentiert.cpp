//#include <stdio.h>
#define NULL 0

// gegebene struct
struct intElem{
	int info;
	intElem *pred, *succ;
};

class intList {
protected:
	// Konstante für die zur Verfügung stehenden freien Speicherplätze
	static const int N = 1000;
	// Zeiger auf die Listenelement (Speicher)
	intElem* memory[N];
public:
	// Konstruktor
	// initialisiert den Speicher mit NULL
	intList() {
		int i;
		for( i = 0; i < N; i++ ) {
			this->memory[i] = NULL;
		}
	}
	
	// Aufgabe 1. a)
	// Methode, die ein freies Element im Speicher ermittelt und dynamisch
	// Speicher reserviert
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
	
	// Aufgabe 1. b)
	// Methode, die Speicherplatz mit NULL-Zeiger (freier Speicher) belegt und
	// den Speicherplatz wieder freigibt
	void free( intElem* el) {
		for( int i = 0; i < N; i++ ) {
			if( this->memory[i] == el ){
				this->memory[i] = NULL;
				break;
			}				
		}
		delete el;		
	};
	
	// Aufgabe 2. a)
	// Methode, die ein Element geordnet in die Liste einfügt
	intElem* insertSorted( intElem* head, int z ) {
		intElem* insert;
		// freien Speicherplatz beschaffen
		insert = this->request();
		// einfügen nicht möglich, wenn kein Speicher vorhanden
		if( insert == NULL )
			return head;
		else {
			insert->pred = NULL;
			insert->succ = NULL;
			insert->info = z;
		}
		// keine Liste vorhanden -> Element ist das einzigste in der neuen
		if( head == NULL )
			return insert;
		intElem* tmp = head;
		while( true ) {
			if( tmp->info >= z ) {
				// am Anfang einfügen
				if( tmp == head ) {
					insert->succ = head;
					insert->succ->pred = insert;
					return insert;
				}
				// in der Mitte einfügen
				insert->pred = tmp->pred;
				insert->succ = tmp;
				insert->pred->succ = insert;
				insert->succ->pred = insert;
				return head;
			}
			// Auslagerung aus while-Schleife, damit das letzte Element
			// erhalten bleibt, an das angehängt werden soll
			if( tmp->succ == NULL )
				break;
			tmp = tmp->succ;
		}
		// am Ende einfügen
		insert->pred = tmp;
		insert->pred->succ = insert;
		return head;
	};
	
	// Aufgabe 2. b)
	// Methode, überprüft, ob eine gegebene Zahl vorhanden ist
	bool exists( intElem* head, int z ) {
		while( head != NULL ) {
			if( head->info == z )
				return true;
			head = head->succ;
		}
		return false;
	};
	
	// Aufgabe 2. c)
	// Methode, um eine gegebene Zahl aus der Liste zu entfernen
	intElem* remove( intElem* head, int z ) {
		intElem* tmp = head;
		while( tmp != NULL ) {
			if( tmp->info == z ){				
				if( tmp->pred == NULL ) {
					// am Anfang der Liste löschen (2. Element neuer Kopf)
					head = tmp->succ;
					head->pred = NULL;
				} else {
					// Vorgänger erhält Nachfolger des löschenden ELements als
					// Nachfolger
					tmp->pred->succ = tmp->succ;				
				}
				// wenn nicht am Ende der Liste, bekommt der Nachfolger einen
				// neuen Vorgänger
				if( tmp->succ != NULL )
					tmp->succ->pred = tmp->pred;
				// Speicherplatz freigeben
				this->free( tmp );
			}
			tmp = tmp->succ;
		}
		return head;
	};
	
	// Ausgabe der Liste
	/*void print( intElem* head ) {
		printf("LIST\n");
		int i = 1;
		while( head != NULL ) {
			printf("%3i ", head->info);
			head = head->succ;
			if( i%10 == 0 )
				printf("\n");
			i++;
		}
		printf("\n\n");
	}*/
	
	// Ausgabe des Speichers
	/*void printMemory() {
		printf("MEMORY\n");
		for( int i = 0; i < this->N; i++ ) {
			if(this->memory[i] == NULL)
				printf("### ");
			else
				printf("%3i ", this->memory[i]->info);	
			if( (i+1)%10 == 0 )
				printf("%i\n", i);
						
		}
		printf("\n");
	}*/
};

int main() {
	// es gibt einen Zeiger auf den Kopf der Liste (h), damit mehrere Listen im 
	// Speicher liegen können
	intList l;
	intElem* h = NULL;
	// Aufgabe 3. a)
	for( int i = 2; i <= 50; i++ ) {
		h = l.insertSorted( h, i );
	}
//	l.printMemory();
//	l.print(h);
//	printf("remove mod 2\n");
	for( int i = 2; i <= 50; i++) {
		if( i%2 == 0 ) {
			h = l.remove(h, i);
		}
	}
//	l.printMemory();
//	l.print(h);
//	printf("remove mod 3\n");
	for( int i = 2; i <= 50; i++) {
		if( i%3 == 0 ) {
			h = l.remove(h, i);
		}
	}
//	l.printMemory();
//	l.print(h);
//	printf("remove mod 5\n");
	for( int i = 2; i <= 50; i++) {
		if( i%5 == 0 ) {
			h = l.remove(h, i);
		}
	}
//	l.printMemory();
//	l.print(h);
	// Ende Aufgabe 3. a)
	
	// Einfügetests:
	// Mitte
	h = l.insertSorted( h, 13);
	// Ende
	h = l.insertSorted( h, 132);
	// Anfang
	h = l.insertSorted( h, 1);
//	l.printMemory();
//	l.print(h);
	return 0;
}

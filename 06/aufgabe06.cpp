#include <stdio.h>

#define A 0
#define C 1
#define D 2
#define F 3
#define G 4
#define L 5
#define R 6
#define S 7
#define Z 8

#define INFINITE 99

class dijkstra {
private:	
	// Konstante für die Anzahl an Knoten im Graphen
	static const int N = 9;
	// Adjazenzmatrix
	int am[N*N];
	// Kostenmatrix (späteres Ergebnis des Algorithmus)
	int costs[N];
	// Enthält bereits abgearbeitete Knoten
	bool processed[N];
public:
	// Initialisiert Adjazenzmatrix mit 0, abgearbeitete Knoten mit false und
	// alle Kosten mit Unendlich
	// erstellt ebenso den in der Aufgabe gegebenen Graphen
	dijkstra() {
		for( int i = 0; i < N*N; i++ ) {
			this->am[i] = 0;
		}
		insert(A, C, 15);
		insert(C, F, 30);	
		insert(C, G, 10);
		insert(C, R, 25);
		insert(C, S, 10);
		insert(C, Z, 30);
		insert(F, D, 20);
		insert(D, R, 15);
		insert(R, G, 10);
		insert(R, L, 20);
		insert(G, L, 40);
		insert(S, Z, 10);
		
		for( int i = 0; i < N; i++ ) {
			this->costs[i] = INFINITE;
			this->processed[i] = false;
		}
	};
	
	// fügt symmetrisch die Gewichte in die Adjazenzmatrix ein
	void insert( int from, int to, int value ) {
		this->am[from * this->N + to] = value;
		// symmetrisch, da ungerichteter Graph
		this->am[to * this->N + from] = value;
	};
	
	// Ausgabefunktion für den Graphen und die ermittelten minimalen Kosten
	/*void print() {		
		for( int i = 0; i < N*N; i++ ) {
			if( i != 0 and i%N == 0)
				printf("\n");
			printf("%4i", this->am[i]);
		}
		printf("\n\n");
		printf("%4s%4s%4s%4s%4s%4s%4s%4s%4s\n", 
			"A", "C", "D", "F", "G", "L", "R", "S", "Z");
		
		for( int i = 0; i < N; i++ ) {
			printf("%4i", this->costs[i]);		
		}
		printf("\n");
	};*/
	
	// überprüft, ob noch unabgearbeitete Knoten vorhanden sind
	bool empty() {
		for( int i = 0; i < N; i++ ) {
			if( this->processed[i] == false )
				return false;
		}
		return true;
	};
	
	// ermittelt den billigsten Knoten
	int cheapest() {
		int min = -1;
		for( int i = 0; i < N; i++ ) {
			if( this->processed[i] == false ) {
				if( min >= 0 and this->costs[i] <= this->costs[min] )
					min = i;
				else 
					if( min < 0 )
						min = i;
			}
		}
		if( this->costs[min] == INFINITE )
			return -1;			// vom Wurzelknoten nicht erreichbare Knoten
										 
		return min;
	};
	
	// Funktion, die Startknoten übergeben bekommt und dann den 
	// Dijkstra-Algorithmus anwendet
	void start( int node ) {
		this->costs[node] = 0;
		while(not empty()) {
			// blligsten suchen
			int c = cheapest();
			if( c == -1 )
				break;			// vom Wurzelknoten nicht erreichbare Knoten
			// markieren
			this->processed[c] = true;
			for( int i = 0; i < N; i++ ) {
				int index = N * c + i;
				// alle adjazenten Knoten:
				if( this->am[index] != 0 ) {
					int curCosts =  this->costs[c] + this->am[index];
					if( curCosts < this->costs[i] ) {
						this->costs[i] = curCosts;
					}
				}
			}
		}
	};

};

int main(){
	dijkstra d;
	d.start(Z);
//	d.print();
	return 0;
}

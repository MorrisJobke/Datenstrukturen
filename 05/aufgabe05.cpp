#include <stdio.h>

class BTreeNode {
private:
	// Elternknoten
	BTreeNode* parent;
	// Schlüsselwerte, die gespeichert werden sollen	
	int* values;
	// Kind-Knoten
	BTreeNode** children[4];
	// Grad der Ordnung des Knotens/Baums
	int order;
public:
	BTreeNode( int o ) {
		this->values = new int[o];			// größeres Array, da Überfüllung
		this->order = o;
		BTreeNode** children[o];
		for( int i = 0; i < o; i++ ) {
			this->values[i] = NULL;
			//this->children[i] = NULL;
		}
	};

	int length() {
		int a = 0;
		
		return a;
	};
	
	void insert( int key ) {
		this->values[1] = key;
	};
	
	void print( int indent ) {	
		this->children[0] = NULL;
		this->values[1] = 33;	
		for( int i = 0; i < indent; i++ )
			printf("\t");	
		for( int i = 0; i < this->order; i++ )
			printf("%3i", this->values[i]);
		printf("\n");
	}
};

class BTree {
private:
	int order;
	
	
	
	BTreeNode* head;
public:
	// Konstruktor, der Ordnung m des Baumes übergeben bekommt
	BTree( int m ) {
		this->order = m;
		this->head = NULL;
	};
	
	// Desktuktor
	~BTree() {
	
	};
	
	// Methode, um einen Schlüssel einzufügen
	void insert( int key ) {
		if( this->head == NULL ) {
			this->head = new BTreeNode( this->order );
			this->head->print(0);
			this->head->insert(key);
			this->head->print(0);
		}
	};
	
	// Methode, um zu überprüfen, ob ein Schlüssel existiert
	bool exists( int key ) {
		
	};
	
	// Methode, um einen Schlüssel zu entfernen
	void remove( int key ) {
	
	};	
};

int main() {
	BTree b(5);
	b.insert(3);
	
	return 0;
}

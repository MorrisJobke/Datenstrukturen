#include <stdio.h>

class BTree {
private:	
	struct BTreeNodeKey {
		BTree* left;			// linker Teilbaum des Elements
		BTreeNodeKey* succ;		// nächstes Element
		int	key;
		BTreeNodeKey( int key ) {
			left = NULL;
			succ = NULL;
			key = key;
		};
	};

	int order;
	
	BTree* parent;			// Elternelement
	BTreeNodeKey* node;		// Elemente des Knotens	mit ihren jeweils linken
							// Teilbäumen
	BTree* right;			// letzter (rechter) Teilbaum
		
public:
	// Konstruktor, der Ordnung m des Baumes übergeben bekommt
	BTree( int m ) {
		order = m;
		parent = NULL;
		node = NULL;
		right = NULL;
	};
	
	// Desktuktor
	~BTree() {
	
	};
	
	int length() {
		int a = 0;
		BTreeNodeKey* tmpNodeKey = node;
		while( tmpNodeKey != NULL ) {
			a++;
		}		
		return a;
	};
	
	BTree* getInsertNode( int key ) {
		BTree* tmp
		if
	};
	
	// Methode, um einen Schlüssel einzufügen
	void insert( int key ) {
		if( node == NULL )
			return;
		else {
			BTree* tmpNode = getInsertNode( key );
			BTreeNodeKey* tmp = new BTreeNodeKey( key );
		}
	};
	
	// Methode, um zu überprüfen, ob ein Schlüssel existiert
	bool exists( int key ) {
		if( node == NULL )
			return false;
		BTreeNodeKey* tmpNodeKey = node;
		while( tmpNodeKey ) {
			if( tmpNodeKey->key < key )
				tmpNodeKey = tmpNodeKey->succ;
			else {
				if( tmpNodeKey->key == key )	
					return true;
				else							// tmpNodeKey->key > key
					return tmpNodeKey->left != NULL and 
						tmpNodeKey->left->exists( key );
			}
		}
		if( right == NULL )
			return false;
		return right->exists( key );
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

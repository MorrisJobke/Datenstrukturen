#include <stdio.h>



class BTreeNode {
private:
	BTreeNode* parent;
	
	struct BTreeNodeEntry {
		BTreeNodeEntry *pred, *succ;
		BTreeNode* child;
		int info;	
	};
	
	BTreeNodeEntry* head;
	
	// first Child
	BTreeNode* treeChild;
	
	int order;
public:
	BTreeNode( int m) {
		this->head = NULL;
		this->order = m;
	};

	int length() {
		int a = 0;
		BTreeNodeEntry* tmp = this->head;
		while(tmp != NULL) {
			tmp = tmp->pred;
			a++;
		}
		return a;
	};
	
	void insert( int key ) {
		
	};
};

class BTree {
private:
	int M;
	BTreeNode* head;
public:
	// Konstruktor, der Ordnung m des Baumes übergeben bekommt
	BTree( int m ) {
		this->M = m;
		this->head = NULL;
	};
	
	// Desktuktor
	~BTree() {
	
	};
	
	// Methode, um einen Schlüssel einzufügen
	void insert( int key ) {
		if( this->head == NULL ) {
			
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
	BTree b(3);
	
	return 0;
}

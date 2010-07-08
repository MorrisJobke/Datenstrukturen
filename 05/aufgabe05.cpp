#include <stdio.h>



class BTreeNode {
private:
	BTreeNode* parent;
	
	struct BTreeNodeEntry {
		BTreeNodeEntry *pred, *succ;
		BTreeNode* child;
		int info;
		BTreeNodeEntry() {
			pred = NULL;
			succ = NULL;
		};	
	};
	
	BTreeNodeEntry* head;
	
	// first Child
	BTreeNode* treeChild;
	
	int order;
public:
	BTreeNode( int o ) {
		this->head = NULL;
		this->order = o;
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
		if( this->head == NULL ) {
			this->head = new BTreeNodeEntry();
			this->head->info = key;
		} else {
			BTreeNodeEntry* tmp = this->head;
			BTreeNodeEntry* tmpInsert = new BTreeNodeEntry();
			if( tmp->info > key )
			{
			}
			while( tmp->succ ) {
				if( tmp->succ->info < key )
					tmp = tmp->succ;	
				else
					break;
			}
		}
	};
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

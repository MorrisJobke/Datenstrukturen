#include <stdio.h>

typedef unsigned short ipType;

class BinarySearchTree {
private:
	struct treeElem {
		const char* string;
		treeElem* next;
		treeElem( const char* s) {
			string = s;
			next = NULL;
		}
	};

	struct treeNode {
		treeElem* headElem;
		char key;
		treeNode* left;
		treeNode* right;
		treeNode(const char* s) {
			headElem = new treeElem(s);
			key = s[0];
			left = NULL;
			right = NULL;
		}
	};
	
	treeNode* root;
	
public: 
	BinarySearchTree() {
		this->root = NULL;
	};
	
	bool exists( const char* s, treeNode* t ) {
		if( t == NULL )
			t = this->root;
		char key = s[0];
		if( key < 'a' or key > 'z' ) {
			if( key <= 'Z' and key >= 'A' )
				key += 32;
			else
				return false;
		}
		if( not ( this->root == NULL ) ) {
			
			printf("%s\n", s);
		}
		return false;
	};
	
	void insert( const char* s ) {
		if( this->root == NULL ) {
			root = new treeNode(s);
		} else {
		
		}
	}

};

int main(){
	BinarySearchTree b;
	b.insert("huhu");
	b.exists("huhu", NULL);
	
//	printf("%i\n", "a"[0]);
//	printf("%i\n", "z"[0]);
//	printf("%i\n", "A"[0]);
//	printf("%i\n", "Z"[0]);
}

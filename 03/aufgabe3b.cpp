#include <stdio.h>
//#define NULL 0

class TreeElem {
private:
	char* string;
	TreeElem* next;
	
public:
	TreeElem(const char* s) {
//		int i = 0;
//		char c = s[i];
//		while( c ) {
//			char d = c;
//			this->string[i] = &d;
//			c = s[++i];
//			if(i >= 100)
//				break;
//		}	
		while( *string++ = *s++ );	
		this->next = NULL;
	};
	
	void insert(const char* s) {
		if( this->next == NULL ){
			this->next = new TreeElem(s);
		}else 
			this->next->insert(s);
	};
	
	bool exists(const char* s) {
		TreeElem* tmp = this;
		while( tmp ) {
			if( this->compare(tmp->string, s) )
				return true;
			else
				tmp = tmp->next;			
		}
		return false;
	};	
	
	static bool compare( const char* s1, const char* s2) {
		char a, b;
		int i = 0;
		a = s1[i];
		b = s2[i];
		while( a or b ){
			if( not (a == b) )
				return false;
			i++;
			a = s1[i];
			b = s2[i];
		}
		return true;
	};
	
	void print() {
		TreeElem* tmp = this;
		while( tmp ) {
//			printf("%s\n", this->string);
		}
	};

};

class BinaryTree {
private:
	BinaryTree* left;
	BinaryTree* right;
	char key;
	TreeElem* head;
public:
	BinaryTree(const char* s) {
		this->left = NULL;
		this->right = NULL;
		this->key = s[0];
		this->head = new TreeElem(s);
	};
	
	static char normalize(char c){
		if( c < 'a' or c > 'z' ) {
			if( c <= 'Z' and c >= 'A' )
				c += 32;
			else
				return NULL;
		}
		return c;
	};
	
	void insert(const char* s) {
		char curKey = this->normalize(s[0]);
		if( not curKey )
			return;		
		if(curKey == this->key)
			this->head->insert(s);
		else {
			if( curKey > this->key ) {			
				if( this->right == NULL ) 
					this->right = new BinaryTree(s);
				else
					this->right->insert(s);
			} else {
				if( this->left == NULL ) 
					this->left = new BinaryTree(s);
				else
					this->left->insert(s);
			}
		}
	};
	
	bool exists(const char* s) {
		char curKey = this->normalize(s[0]);
		if( not curKey )
			return false;
		if(curKey == this->key)
			return this->head->exists(s);
		else {
			if( curKey > this->key ) {			
				if( this->right == NULL ) 
					return false;
				else
					return this->right->exists(s);
			} else {
				if( this->left == NULL ) 
					return false;
				else
					return this->left->exists(s);
			}
		}
	};
	
	void print() {
		this->left->print();
	};
};

int main() {
	BinaryTree* r = new BinaryTree("huhu");
	r->insert("moin");
	r->insert("wert");
	r->insert("jawohl");
	r->insert("Nein");
	printf("Nein existiert");
	if(r->exists("Nein"))
		printf("\n");
	else
		printf(" nicht\n");
	r->insert("moin");
	
	//r->print();
	
	
	
}

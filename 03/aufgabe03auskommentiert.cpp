//#include <stdio.h>
#define NULL 0

// maximale Länge einer Zeichenkette 100 + NULLBYTE 
const int size = 101;
// Typdefinition für Zeichenkette
typedef char string[size];
	
// Elemente eines Knotens als verkettete Liste
struct NodeElem {
	NodeElem *succ;
	string info;
	NodeElem( string s ) {
		for( int i = 0; i < size; i++ ) {
			info[i] = s[i];
		}
		succ = NULL;
	};
};
	
// Knoten des Binärbaumes
struct TreeNode {
	NodeElem *head;							// Zeiger auf Elemente dieses Knotens
	char key;
	TreeNode *left, *right;
	TreeNode( char k ) {
		key = k;
		left = NULL;
		right = NULL;
		head = NULL;
	};
};

class StringTree {
private:
	// Kopf des Baumes
	TreeNode *head;
	
	// Methode, um den Knoten im Baum zu finden, der den Schlüssel "key" hat
	// NULL wenn dieser nicht gefunden wird
	TreeNode* getTreeNode( char key ) {		
		TreeNode* tmp = head;
		while(tmp != NULL) {
			if( tmp->key == key )
				break;
			if( tmp->key < key )
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}	
		return tmp;
	};
public:
	// Konstruktor
	StringTree() {
		head = NULL;
	};
	
	// Aufgabe b
	// Methode, um zu überprüfen, ob eine gegebene Zeichenkette im Baum vorhanden ist
	bool exists( string s ) {
		// Knoten finden
		TreeNode* tmp = getTreeNode( s[0] );		
		if( tmp == NULL )	
			return false;						// kein Knoten gefunden
		NodeElem* tmpList = tmp->head;
		while(tmpList != NULL) {
			bool foundKey = true;
			// Vergleich der beiden Zeichenketten
			for( int i = 0; i < size; i++ ) {
				if(tmpList->info[i] != s[i]) {	// Unterschied gefunden
					foundKey = false;
					break;
				}
			}
			if(foundKey == true)				// beide Zeichenketten identisch
				return true;
			// bei keinem Fund - gehe zum Nächsten Element in der Liste
			tmpList = tmpList->succ;
		}
		// Zeichenkette nicht gefunden
		return false;
	};
	
	// Aufgabe c
	// Methode, die die Anzahl der Elemente zu einem Schlüssel liefert
	int count( char key ) {
		// Knoten finden
		TreeNode* tmp = getTreeNode( key );
		if( tmp == NULL )							// Knoten nicht gefunden -> 0 Elemente
			return 0;
		int c = 0;
		NodeElem* tmpList = tmp->head;
		// Liste komplett durchlaufen und mitzählen
		while(tmpList != NULL) {
			tmpList = tmpList->succ;
			c++;
		}
		return c;
	};

	// Aufgabe d
	// Methode, um eine Zeichenkette in den Baum einzufügen
	void insert( string s ) {
		TreeNode* tmp = head;
		if( tmp == NULL ) {							// kein Baum vorhanden - Baum erstellen
			tmp = new TreeNode( s[0] );
			head = tmp;
		} else {
			// Knotensuche		
			while(tmp != NULL) {
				if( tmp->key == s[0] )					// passenden Knoten gefunden
					break;
				if( tmp->key < s[0] ){					// passender Knoten ist im rechten Teilbaum
					if( tmp->right == NULL ) {			// rechter Teilbaum ist leer - neuen Teilbaum erstellen
						TreeNode* in = new TreeNode( s[0] );
						tmp->right = in;
					}
					tmp = tmp->right;					
				} else {								// passender Knoten ist im linken Teilbaum
					if( tmp->left == NULL ) {			// linker Teilbaum ist leer - neuen Teilbaum erstellen
						TreeNode* in = new TreeNode( s[0] );
						tmp->left = in;
					}
					tmp = tmp->left;
				}
			}
		}
		// Element erstellen
		NodeElem* node = new NodeElem( s );
		// Element am Anfang der Liste einfügen
		node->succ = tmp->head;
		tmp->head = node;
	};
	
	
};

int main() {
	StringTree st;
	string s1 = { 'a', 'b', '\0' };
	string s2 = { 'D', 'b', 's', 'a', '\0' };
	string s3 = { 'z', 'B', 'a', 'B', 'a', 'B', '\0' };
	string s4 = { 'c', 'b', '\0' };
	string s5 = { '4', 'b', '\0' };
	st.insert(s1);
	st.insert(s2);
	st.insert(s3);
	st.insert(s4);
	st.insert(s1);
	st.insert(s5);
//	printf("%s\n", st.exists(s1) ? "t" : "f");
//	printf("%c - %i\n", s1[0], st.count(s1[0]));
//	printf("%c - %i\n", s2[0], st.count(s2[0]));
//	printf("%c - %i\n", s3[0], st.count(s3[0]));
//	printf("%c - %i\n", s4[0], st.count(s4[0]));
//	printf("%c - %i\n", s5[0], st.count(s5[0]));
	return 0;
};

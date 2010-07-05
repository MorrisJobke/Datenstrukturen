#define NULL 0

// gegebenes struct für Baum-Knoten
struct tree {
	int info;
	int balance;
	tree* left, *right;
};

// Funktion, die Maximalwert zweier Zahlen zurückliefert
int max( int a, int b ) {
	if( a > b )
		return a;
	return b;
};

// Funktion, die die Länge eines Baumes bestimmt
int length( tree* t ) {
	if( t == NULL )
		return 0;
	return max(length(t->left) + 1, length(t->right) + 1);
};

// Aufgabe 1
// Funktion, die die Balanceinformation in den Baum und seine Unterbäume 
// schreibt
void balance( tree* t ) {
	if( t->left != NULL )
		balance( t->left );
	if( t->right != NULL )
		balance( t->right );
	t->balance = length(t->right) - length(t->left);
};

int main() {
	return 0;
}

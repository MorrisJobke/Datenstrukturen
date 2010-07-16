#include <stdio.h>

struct treeNode{
	treeNode* left;
	treeNode* right;
	int info;
	treeNode() {
		left = NULL;
		right = NULL;
	};
};

class queue{
private:	
	struct queueNode {
		treeNode* t;
		queueNode* next;
		queueNode(treeNode* tree) {
			next = NULL;
			t = tree;
		};
	};
	queueNode* head;
	queueNode* last;
public:
	queue() {
		head = NULL;
		last = NULL;
	};
	
	bool unEmpty() {
		if(head == NULL)
			return false;
		return true;
	};
	
	void enqueue(treeNode* t){
		queueNode* tmp = new queueNode(t);
		if(last != NULL)
			last->next = tmp;
		else {
			head = tmp;
		}
		last = tmp;
	};
	
	treeNode* unqueue(){
		if(head == NULL){
			last = NULL;
			return NULL;
		}
		queueNode* tmp = head;
		treeNode* tmpTree = tmp->t;	
		head = tmp->next;	
		delete tmp;	
		return tmpTree;		
	};
};

class binaryTree {
private:
	
	treeNode* head;
public:
	binaryTree() {
		head = NULL;
	};
	
	void insert(int info) {
		treeNode* tmpInsert = new treeNode;
		tmpInsert->info = info;
		if(head == NULL) {
			head = tmpInsert;
			return;
		} 
		treeNode* tmp = head;
		while(true){
			if(tmp->info > info) {
				if(tmp->left == NULL){
					tmp->left = tmpInsert;
					return;
				}
				tmp = tmp->left;
			} else {	
				if(tmp->info == info)
					return;
				if(tmp->right == NULL){
					tmp->right = tmpInsert;
					return;
				}
				tmp = tmp->right;
			}
		}		
	};
	
	void print() {
		queue* q = enqueue(NULL, head);
		int c = 0;
		while(q->unEmpty()) {
			treeNode* tmp = q->unqueue();	
			switch(tmp->info) {
				case -1:
					//printf(")");
					c--;	
					break;
				case -2:
					//printf("(");	
					c++;
					break;
				default:
					for(int i = 0; i < c; i++)
						printf("\t");
					if(c == 0)
						printf("\n");
					printf("%i\n", tmp->info);
					break;
			}
		}
		printf("\n");
	};
	
	queue* enqueue(queue* q, treeNode* t) {
		if(q == NULL)
			q = new queue;
		if(t != NULL ) 	{				
			q->enqueue(t);	
			treeNode* tmp = new treeNode();
			tmp->info = -2;
			q->enqueue(tmp);
			q = enqueue(q, t->left);
			q = enqueue(q, t->right);
			tmp = new treeNode();
			tmp->info = -1;
			q->enqueue(tmp);			
		}
		return q;
	};
	
	// Übung 06 Aufgabe 1 i
	int countLeaves(treeNode* t){
		if( t == NULL )
			t = head;
		if(t->left == NULL and t->right == NULL)
			return 1;
		if(t->left == NULL)
			return countLeaves(t->right);
		if(t->right == NULL)
			return countLeaves(t->left);
		return countLeaves(t->left) + countLeaves(t->right);
	};
	
	// Übung 06 Aufgabe 1 ii
	int getHeight(treeNode* t){
		if( t == NULL )
			t = head;
		if(t->left == NULL and t->right == NULL)
			return 1;
		if(t->left == NULL)
			return getHeight(t->right) + 1;
		if(t->right == NULL)
			return getHeight(t->left) + 1;
		int a = getHeight(t->left);
		int b = getHeight(t->right);
		if(a < b)
			return b + 1;
		return a + 1;
	};
	
	void flip(treeNode* t) {
		if(t == NULL)
			t = head;
		if(t->left != NULL)
			flip(t->left);
		if(t->right != NULL)
			flip(t->right);
		treeNode* tmp = t->left;
		t->left = t->right;
		t->right = tmp;		
	};
	
};

int main() {
	binaryTree a;
	a.insert(17);
	a.insert(10);
	a.insert(21);
	a.insert(9);
	a.insert(13);
	a.insert(39);
	a.insert(33);
	a.insert(76);
	a.insert(23);
	a.insert(36);
	a.insert(35);
	a.insert(45);
	a.insert(99);
	a.insert(63);
	a.print();
	printf("%i\n", a.countLeaves(NULL));
	printf("%i\n", a.getHeight(NULL));
	a.flip(NULL);
	a.print();
	return 0;
}

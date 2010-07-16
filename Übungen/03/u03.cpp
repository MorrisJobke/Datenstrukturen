#include <stdio.h>

typedef int ELEMENTTYP;

struct node {
	ELEMENTTYP info;
	node *next;
};

node* createList() {
	return NULL;
};

bool isEmpty(node* l) {
	if( l == NULL )
		return true;
	return false;
};

void writeList(node* l) {
	node* tmp = l;
	while(tmp != NULL) {
//		printf("%i %i\n", tmp, tmp->info);
		printf("%i\n", tmp->info);
		tmp = tmp->next;
	}
};

node* insertAtHead(node* l, ELEMENTTYP info) {
	node* tmp = new node;
	tmp->info = info;
	tmp->next = l;
	return tmp;
};

node* insertAtTail(node* l, ELEMENTTYP info) {
	node* tmpInsert = new node;
	tmpInsert->info = info;
	tmpInsert->next = NULL;
	if(l == NULL)
		return tmpInsert;
	node* tmp = l;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = tmpInsert;
	return l;
};

node* search(node* l, ELEMENTTYP info) {
	if( l == NULL )
		return NULL;
	if( l->info == info )
		return l;
	return search(l->next, info);
};

node* insertSorted(node* l, ELEMENTTYP info) {
	if( l == NULL or l->info > info )
		return insertAtHead(l, info);
	node* tmp = l;
	node* tmpInsert = new node;
	tmpInsert->info = info;
	while(tmp->next != NULL) {
		if(tmp->next->info >= info) {
			node* tmpNext = tmp->next;
			tmp->next = tmpInsert;
			tmpInsert->next = tmpNext;
			return l;
		}
		tmp = tmp->next;
	}
	tmp->next = tmpInsert;
	tmpInsert->next = NULL;
	return l;
};

node* deleteFirst(node* l) {
	if(l == NULL)
		return NULL;
	node* tmp = l->next;
	delete l;
	return tmp;
};

node* deleteSpecific(node* l, ELEMENTTYP info) {
	if(l == NULL)
		return NULL;
	if(l->info == info) {
		node* tmpNext = l->next;
		delete l;
		return tmpNext;
	}
	node* tmp = l;
	while(tmp->next != NULL) {
		if(tmp->next->info == info) {
			node* tmpNext = tmp->next;
			tmp->next = tmpNext->next;
			delete tmpNext;
			return l;
		}
		tmp = tmp->next;
	}
	return l;
};

node* mirror(node* l) {
	if(l == NULL)
		return NULL;
	node* tmp = new node;
	tmp->info = l->info;
	tmp->next = mirror(l->next);
	return tmp;
};

ELEMENTTYP getMin(node* l) {
	if(l == NULL)
		return -1;
	ELEMENTTYP min = l->info;
	while(l != NULL) {
		if(l->info < min)
			min = l->info;
		l = l->next;
	}	
	return min;
};

node* sortList(node* l) {
	node* tmp = createList();
	while(!isEmpty(l)){
		node* tmpAppend = new node();
		ELEMENTTYP a = getMin(l);
		l = deleteSpecific(l, a);
		tmp = insertAtTail(tmp, a); 
	}
	return tmp;
};

int main() {
	node* h = createList();
	if(isEmpty(h))
		printf("empty\n");
	else
		printf("not empty\n");
	h = insertAtHead(h, 4);
	h = insertAtHead(h, 3);
	h = insertAtTail(h, 5);
	h = insertAtTail(h, 8);
	if(isEmpty(h))
		printf("empty\n");
	else
		printf("not empty\n");
//	printf("%i\n", search(h, 3));
	h = insertSorted(h, 1);
	h = insertSorted(h, 4);
	h = insertSorted(h, 7);
	h = insertSorted(h, 10);
	h = deleteFirst(h);
	h = deleteSpecific(h, 10);
	writeList(h);
	printf("%i\n", getMin(h));
//	node* k = mirror(h);
//	writeList(k);
	printf("\n\n");
	node* k = createList();
	k = insertAtTail(k, 5);
	k = insertAtHead(k, 4);
	k = insertAtHead(k, 3);
	k = insertAtTail(k, 8);
	k = insertAtHead(k, 4);
	k = insertAtHead(k, 7);
	k = insertAtHead(k, 9);
	k = insertAtTail(k, 18);
	k = insertAtTail(k, 2);
	k = sortList(k);
	writeList(k);
	
	
	return 0;
};

#include <stdio.h>

struct node {
	int info;
	node *pred, *succ;
	node() {
		succ = NULL;
		pred = NULL;
	};

};

class list {
private:
	node* head;
public:
	list() {
		head = NULL;
	};
	
	void insertAtHead(int info) {
		node* tmp = new node;
		tmp->info = info;
		tmp->succ = head;
		tmp->succ->pred = tmp;
		head = tmp;
	};
	
	void insertAtTail(int info) {
		node* tmpInsert = new node;
		tmpInsert->info = info;
		if(head == NULL)
			head = tmpInsert;
		else {
			node* tmp = head;
			while(tmp->succ != NULL)
				tmp = tmp->succ;
			tmp->succ = tmpInsert;
			tmpInsert->pred = tmp;
		}
	};
	
	bool exists(int info) {
		node* tmp = head;
		while(tmp != NULL) {
			if(tmp->info == info)
				return true;
			tmp = tmp->succ;
		}
		return false;
	};
};

int main() {	
	return 0;
}

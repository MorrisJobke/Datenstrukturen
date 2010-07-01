#include <stdio.h>

typedef unsigned short ipType;

struct ip;
struct router;
struct node;
struct trace;

struct ip {
	ipType first;
	ipType second;
	ipType third;
	ipType fourth;
};

struct router {
	ip* i;
	router* next;
	node* n;
};

struct node {
	ip* i;
	router* r;
	node* previous;
	node* next;
};

struct trace {
	ip* i;
	trace* next;
};

bool sameSubNet(ip* a, ip* b){
	if(	a->first == b->first and
		a->second == b->second and
		a->third == b->third and
		not (a->fourth == b->fourth) )
		return true;
	return false;
}

bool sameIp(ip* a, ip* b){
	if(	a->first == b->first and
		a->second == b->second and
		a->third == b->third and
		a->fourth == b->fourth )
		return true;
	return false;
}

bool isNode(router* r, ip i){
	ip* tmp = r->i;
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		if(sameIp(r->i, tmp))
			return false;
	}
	node* n = r->n;
	if(n == NULL)
		return false;
	while(not sameIp(n->i, &i)){
		if(	n->i->fourth > i.fourth or
			n->next == NULL){
			return false;
		}
		n = n->next;
	}
	return true;
} 

bool isEmpty(node* i){
	if(i == NULL)
		return true;
	return false;
}

void print(router* r){
	if(not r){
		printf("FAIL\n");
		return;
	}
	ip* tmpIp = r->i;
	while(true){
		//printf("router: %i.%i.%i.%i\t\t\town: %i \t\t\t\tnext: %i\n", r->i->first, r->i->second, r->i->third, r->i->fourth, r, r->next);
		printf("router: %i.%i.%i.%i\n", r->i->first, r->i->second, r->i->third, r->i->fourth);
		node* tmpNode = r->n;
		while(not isEmpty(tmpNode)){
			//printf("\tnode: %i.%i.%i.%i\t\town: %i \tprev: %9i \tnext: %i\n", tmpNode->i->first, tmpNode->i->second, tmpNode->i->third, tmpNode->i->fourth, tmpNode, tmpNode->previous, tmpNode->next);
			printf("\tnode: %i.%i.%i.%i\n", tmpNode->i->first, tmpNode->i->second, tmpNode->i->third, tmpNode->i->fourth);
			tmpNode = tmpNode->next;
		}
		r = r->next;
		if(sameIp(r->i, tmpIp)){
			break;
		}
	}
}

void print(trace* t){
	if(not t)
	{
		printf("no trace found\n");
		return;
	}	
	while(t){
		printf("%i.%i.%i.%i -> ", t->i->first, t->i->second, t->i->third, t->i->fourth); 
		t = t->next;
	}
	printf("FINISH\n");
}

router* insertRouter(router*& r, ipType a,  ipType b, ipType c, ipType d){
	router* tmp = new router;
	ip* tmpIp = new ip;
	tmpIp->first = a;
	tmpIp->second = b;
	tmpIp->third = c;
	tmpIp->fourth = d;
	tmp->i = tmpIp;
	tmp->n = NULL;
	if(r == NULL){
		tmp->next = tmp;
		return tmp;
	}
	tmp->next = r->next;
	r->next = tmp;
	return r;
}

router* insertNode(router* r, ipType a, ipType b, ipType c, ipType d){
	node* tmp = new node;
	tmp->r = r;	
	ip* tmpIp = new ip;
	tmpIp->first = a;
	tmpIp->second = b;
	tmpIp->third = c;
	tmpIp->fourth = d;
	tmp->i = tmpIp;
	router* tmpRouter = r;
	if(r == NULL)
		return false;
	while(not sameSubNet(tmpRouter->i, tmpIp)){
		tmpRouter = tmpRouter->next;
		if(sameIp(tmpRouter->i, r->i))
			return false;
	}
	tmp->r = tmpRouter;
	if(tmpRouter->n == NULL){
		tmpRouter->n = tmp;
		tmp->next = NULL;
		tmp->previous = NULL;
		return r;
	}
	node* tmpNode = tmpRouter->n;
	while(tmpNode->i->fourth < tmp->i->fourth){
		if(tmpNode->next == NULL){
			tmpNode->next = tmp;
			tmp->previous = tmpNode;
			tmp->next = NULL;
			return r;
		}		
		tmpNode = tmpNode->next;	
	}
	if(tmpNode->previous == NULL){
		tmpRouter->n = tmp;
		tmpNode->previous = tmp;
		tmp->next = tmpNode;
		tmp->previous = NULL;
		return r;
	}
	tmpNode->previous->next = tmp;
	tmp->previous = tmpNode->previous;
	tmp->next = tmpNode;
	tmpNode->previous = tmp;
	return r;
}

node* getNode(router* r, ip i){
	ip* tmp = r->i;
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		if(sameIp(r->i, tmp))
			return false;
	}
	node* n = r->n;
	if(n == NULL)
		return false;
	while(not sameIp(n->i, &i)){
		if(	n->i->fourth > i.fourth or
			n->next == NULL){
			return false;
		}
		n = n->next;
	}
	return n;
}

trace* appendTrace(trace* t, ip* i){
	trace* tmp = new trace;
	tmp->next = NULL;
	tmp->i = i;
	
	trace* tmpTrace = t;
	if(t == NULL)
		return tmp;
	while(tmpTrace->next)
		tmpTrace = tmpTrace->next;
	tmpTrace->next = tmp;
	return t;
}

trace* routeIt(node* n, ip i){
	router* r = n->r;
	if(not isNode(r, i))
		return NULL;
	trace* t = appendTrace(NULL, n->i);
	t = appendTrace(t, r->i);
	
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		t = appendTrace(t, r->i);
	}
	t = appendTrace(t, &i);
	return t;
}


int main(){
	printf("starting ...\n");
	router* h;
	h = NULL;
	h = insertRouter(h, 1, 1, 1, 1);
	h = insertRouter(h, 1, 2, 2, 1);
	h = insertRouter(h, 1, 1, 3, 1);
	h = insertRouter(h, 1, 1, 4, 1);
	h = insertNode(h, 1, 1, 1, 2);
	h = insertNode(h, 1, 2, 2, 7);
	h = insertNode(h, 1, 2, 2, 3);
	h = insertNode(h, 1, 2, 2, 9);
	h = insertNode(h, 1, 2, 2, 5);
	h = insertNode(h, 1, 2, 2, 4);
	h = insertNode(h, 1, 2, 2, 8);
	h = insertNode(h, 1, 1, 4, 5);
	h = insertNode(h, 1, 1, 4, 8);
	h = insertNode(h, 1, 1, 3, 2);
	h = insertNode(h, 1, 1, 3, 7);
	ip i;
	i.first = 1;
	i.second = 2;
	i.third = 2;
	i.fourth = 4;
	printf("%i.%i.%i.%i", i.first, i.second, i.third, i.fourth);
	if(isNode(h, i))
		printf(" is node\n");
	else
		printf(" is not node\n");
	
	ip a, b;
	a.first = 1;
	a.second = 2;
	a.third = 2;
	a.fourth = 4;
	b.first = 1;
	b.second = 1;
	b.third = 3;
	b.fourth = 2;
	
	print(routeIt(getNode(h, a), b));
	
	
	print(h);
	return 0;
}

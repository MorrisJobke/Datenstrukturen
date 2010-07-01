#include <stdio.h>

//Typ der IP-Ziffern (0-255)
typedef unsigned short ipType;

//Deklarationen
struct ip;
struct router;
struct node;
struct trace;

//struct für eine IP-Adresse (first.second.third.fourth)
struct ip {
	ipType first;
	ipType second;
	ipType third;
	ipType fourth;
};

/*	
struct für einen Router
	i 		- IP des Routers
	next	- Zeiger auf nächsten Router (Ringliste)
	n 		- Zeiger auf ersten Rechner im ROuter-Subnetz
*/
struct router {
	ip* i;
	router* next;
	node* n;
};

/*
struct für einen Rechner
	i 		- IP des Rechner
	r 		- Zeiger auf "eigenen" Router (an dem er angeschlossen ist)
	pred	- Zeiger auf Vorgänger
	succ	- Zeiger auf Nachfolger
*/
struct node {
	ip* i;
	router* r;
	node* pred;
	node* succ;
};

/*
struct für einen Weg
	i 		- IP des Wegpunktes (Rechner/Router)
	next	- Zeiger auf nächsten Wegpunkt (Rechner/Router)
*/
struct trace {
	ip* i;
	trace* next;
};

/*
Funktion, die 2 IP-Adressen dahingehend vergleicht, ob sie im selben Subnetz sind
Rückgabewert: true/false
*/
bool sameSubNet(ip* a, ip* b){
	if(	a->first == b->first and
		a->second == b->second and
		a->third == b->third and
		not (a->fourth == b->fourth) )
		return true;
	return false;
}

/*
Funktion, die 2 IP-Adressen af Gleichheit überprüft
Rückgabewert: true/false
*/
bool sameIp(ip* a, ip* b){
	if(	a->first == b->first and
		a->second == b->second and
		a->third == b->third and
		a->fourth == b->fourth )
		return true;
	return false;
}

/*
Funktion, die bestimmt, ob sich ein Knoten im Netzwerk befindet (2. Aufgabe)
Rückgabewert: true/false
*/
bool isNode(router* r, ip i){
	ip* tmp = r->i;
	// solange i und die IP des ROuters nicht übereinstimmen:
	//		gehe zum nächsten Router
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		// wieder am Ausgangs-Router angelangt: Abbruch
		if(sameIp(r->i, tmp))
			return false;
	}
	// Router hat die übergebene IP -> Kein Knoten kann diese IP haben
	if(sameIp(r->i, i))
		return false;
	node* n = r->n;
	// Router hat keine angeschlossenen Rechner 
	if(n == NULL)
		return false;
	// Solange Liste durchlaufen bis Rechner-IP und i übereinstimmen
	while(not sameIp(n->i, &i)){
		// Abbruch bei größerer letzter Stelle (geordnete Liste) oder
		// wenn es keinen Nachfolger gibt
		if(	n->i->fourth > i.fourth or
			n->succ == NULL){
			return false;
		}
		n = n->succ;
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
			//printf("\tnode: %i.%i.%i.%i\t\town: %i \tprev: %9i \tnext: %i\n", tmpNode->i->first, tmpNode->i->second, tmpNode->i->third, tmpNode->i->fourth, tmpNode, tmpNode->pred, tmpNode->next);
			printf("\tnode: %i.%i.%i.%i\n", tmpNode->i->first, tmpNode->i->second, tmpNode->i->third, tmpNode->i->fourth);
			tmpNode = tmpNode->succ;
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
		tmp->succ = NULL;
		tmp->pred = NULL;
		return r;
	}
	node* tmpNode = tmpRouter->n;
	while(tmpNode->i->fourth < tmp->i->fourth){
		if(tmpNode->succ == NULL){
			tmpNode->succ = tmp;
			tmp->pred = tmpNode;
			tmp->succ = NULL;
			return r;
		}		
		tmpNode = tmpNode->succ;	
	}
	if(tmpNode->pred == NULL){
		tmpRouter->n = tmp;
		tmpNode->pred = tmp;
		tmp->succ = tmpNode;
		tmp->pred = NULL;
		return r;
	}
	tmpNode->pred->succ = tmp;
	tmp->pred = tmpNode->pred;
	tmp->succ = tmpNode;
	tmpNode->pred = tmp;
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
			n->succ == NULL){
			return false;
		}
		n = n->succ;
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

#include <stdio.h>
//#define NULL 0

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
	if(r == NULL)
		return false;
	ip* tmp = r->i;
	// solange i und die IP des Routers nicht übereinstimmen:
	//		gehe zum nächsten Router
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		// wieder am Ausgangs-Router angelangt: Abbruch
		if(sameIp(r->i, tmp))
			return false;
	}
	// Router hat die übergebene IP -> Kein Knoten kann diese IP haben
	if(sameIp(r->i, &i))
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

/*
redundanter Code
Funktion, wie isNode(), nur dass auch Router-IPs erkannt werden
*/
bool exists(router* r, ip i) {
	if(r == NULL)
		return false;
	ip* tmp = r->i;
	// solange i und die IP des Routers nicht übereinstimmen:
	//		gehe zum nächsten Router
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		// wieder am Ausgangs-Router angelangt: Abbruch
		if(sameIp(r->i, tmp))
			return false;
	}
	// Router hat die übergebene IP -> Kein Knoten kann diese IP haben
	if(sameIp(r->i, &i))
		return true;
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

/*
Ausgabe des Netzwerkes für einen beliebigen Router
*/
void print(router* r){
	if(not r){
		printf("FAIL\n");
		return;
	}
	ip* tmpIp = r->i;
	while(true){
		printf("router: %i.%i.%i.%i\n", 
			r->i->first, r->i->second, 
			r->i->third, r->i->fourth);
		node* tmpNode = r->n;
		while(tmpNode != NULL){
			printf("\tnode: %i.%i.%i.%i\n", 
				tmpNode->i->first, tmpNode->i->second, 
				tmpNode->i->third, tmpNode->i->fourth);
			tmpNode = tmpNode->succ;
		}
		r = r->next;
		if(sameIp(r->i, tmpIp)){
			break;
		}
	}
}


/*
Ausgabe der IP
*/
void print(ip* i){
	if(not i)
		return;
	printf("%i.%i.%i.%i", 
		i->first, i->second, 
		i->third, i->fourth); 
}

/*
Ausgabe des Weges
*/
void print(trace* t){
	if(not t)
	{
		printf("no trace found\n");
		return;
	}	
	while(t){
		print(t->i);
		printf(" -> ");
		t = t->next;
	}
	printf("FINISH\n");
}	

/*
Einfügen eines Routers
*/
router* insertRouter(router* r, ipType a,  ipType b, ipType c, ipType d){
	router* tmp = new router;
	ip* tmpIp = new ip;
	tmpIp->first = a;
	tmpIp->second = b;
	tmpIp->third = c;
	tmpIp->fourth = d;
	// IP existiert bereits
	if(exists(r, *tmpIp)) {
		delete tmpIp;
		delete tmp;
		return r;
	}
	tmp->i = tmpIp;
	tmp->n = NULL;
	// leeres Netzwerk
	if(r == NULL){
		tmp->next = tmp;
		return tmp;
	}
	// Einfügen nach dem übergebenen Router
	// r -> s
	// r -> tmp -> s
	tmp->next = r->next;
	r->next = tmp;
	return r;
}

/*
Einfügen eines Rechners
*/
router* insertNode(router* r, ipType a, ipType b, ipType c, ipType d){
	node* tmp = new node;
	tmp->r = r;	
	ip* tmpIp = new ip;
	tmpIp->first = a;
	tmpIp->second = b;
	tmpIp->third = c;
	tmpIp->fourth = d;
	// IP existiert bereits
	if(exists(r, *tmpIp)) {
		delete tmpIp;
		delete tmp;
		return r;
	}
	tmp->i = tmpIp;
	router* tmpRouter = r;
	// keine Router vorhanden, an die der Rechner angeschlossen werden kann
	if(r == NULL)
		return false;
	while(not sameSubNet(tmpRouter->i, tmpIp)){
		tmpRouter = tmpRouter->next;
		if(sameIp(tmpRouter->i, r->i))
			return false;
	}
	tmp->r = tmpRouter;
	// keine Rechner an Router angeschlossen -> direktes anhängen an Router
	if(tmpRouter->n == NULL){
		tmpRouter->n = tmp;
		tmp->succ = NULL;
		tmp->pred = NULL;
		return r;
	}
	node* tmpNode = tmpRouter->n;
	while(tmpNode->i->fourth < tmp->i->fourth){
		// letzte Rechner hat "kleinere" IP als der anzuhängende und hat keinen
		// Nachfolger
		// 		-> am Ende anhängen
		if(tmpNode->succ == NULL){
			tmpNode->succ = tmp;
			tmp->pred = tmpNode;
			tmp->succ = NULL;
			return r;
		}		
		tmpNode = tmpNode->succ;	
	}
	// vor tmpNode einfügen, da die Bedingung - IP des aktuellen Rechners 
	// (tmpNode) "größer" als die des einzuhängenden - erfüllt wurde
	
	// aktuellen Rechner hat keinen Vorgänger
	//		-> am Anfang einfügen
	if(tmpNode->pred == NULL){
		tmpRouter->n = tmp;
		tmpNode->pred = tmp;
		tmp->succ = tmpNode;
		tmp->pred = NULL;
		return r;
	}
	// in der Mitte einfügen
	tmpNode->pred->succ = tmp;
	tmp->pred = tmpNode->pred;
	tmp->succ = tmpNode;
	tmpNode->pred = tmp;
	return r;
}

/*
Verweis auf einen Knoten anhand der IP erhalten
	Helfer-Funktion für Aufgabe 3
*/
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

/*
Helfer-Funktion, die an die übergebene Route eine IP am Ende anhängt
*/
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

/*
Funktion, die eine Route für einen Zeiger auf einen Knoten und eine Ziel-IP
ermittelt (3. Aufgabe)
*/
trace* routeIt(node* n, ip i){
	router* r = n->r;
	// wenn das Ziel nicht existiert, wird ein NULL-Zeiger zurückgegeben
	if(not isNode(r, i))
		return NULL;
	trace* t = NULL;
	// Erster Punkt auf der Route ist die eigene IP
	// falls die eigene IP nicht mit in der Route auftauchen soll, aus-
	// kommentieren
	t = appendTrace(t, n->i);
	// eigenen Router an Weg anhängen
	t = appendTrace(t, r->i);
	
	// solange Router anhängen, bis dieser im selben Subnetz ist
	// Datenpaket geht auch über Router, wenn Start- und Ziel im gleichen
	// Subnetz (Zusatzaufgabe)
	while(not sameSubNet(r->i, &i)){
		r = r->next;
		t = appendTrace(t, r->i);
	}
	node* tmpN = r->n;
	// solange IPs anhängen, bis man beim gewünschten Rechner ist
	while( not sameIp(tmpN->i, &i)){
		t = appendTrace(t, tmpN->i);	
		tmpN = tmpN->succ;	
	}
	// Ziel-IP anhängen
	t = appendTrace(t, tmpN->i);	
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
	h = insertNode(h, 1, 1, 4, 8);
	h = insertNode(h, 1, 1, 4, 5);
	h = insertNode(h, 1, 1, 3, 2);
	h = insertNode(h, 1, 1, 3, 7);
	h = insertNode(h, 1, 2, 2, 10);
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
	a.second = 1;
	a.third = 4;
	a.fourth = 8;
	b.first = 1;
	b.second = 1;
	b.third = 3;
	b.fourth = 2;
	
	print(routeIt(getNode(h, b), a));
	
	
	print(h);
	return 0;
}

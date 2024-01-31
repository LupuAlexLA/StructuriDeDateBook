#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Laptop Laptop;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Laptop {
	char* marca;
	float pret;
};

struct Nod {
	Laptop info;
	Nod* next;
};

struct HashTable {
	int dim;
	Nod** vector;
};

Laptop initializareLaptop(char* marca, float pret) {
	Laptop l;
	l.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(l.marca, marca);

	l.pret = pret;

	return l;
}

void afisareLaptop(Laptop l) {
	printf("Marca: %s, pret: %f \n", l.marca, l.pret);
}

int functieHash(char* marca, int dim) {
	return strlen(marca) % dim;
}

HashTable initializareHT(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

void inserareFinal(Laptop l, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = l;

	if (*cap == 0) {
		*cap = nou;
	}
	else {
		Nod* temp = *cap;
		while (temp->next != 0) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void inserareHT(HashTable ht, Laptop l) {
	if (ht.dim > 0) {
		int poz = functieHash(l.marca, ht.dim);
		if (poz < ht.dim && poz >= 0) {
			inserareFinal(l, &(ht.vector[poz]));
		}
	}
}

void afisareHash(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod* aux = ht.vector[i];
			printf("Pozitia din hash: %d\n", i);
			while (aux) {
				afisareLaptop(aux->info);
				aux = aux->next;
			}
		}
		else {
			printf("Pozitie goala in Hash %d\n", i);
		}
	}
}

void main() {
	HashTable ht;
	ht = initializareHT(10);

	inserareHT(ht, initializareLaptop("Asus", 100));
	inserareHT(ht, initializareLaptop("HP", 900));
	inserareHT(ht, initializareLaptop("Acer", 700));
	inserareHT(ht, initializareLaptop("Lenovo", 300));
	inserareHT(ht, initializareLaptop("Apple", 2445));

	afisareHash(ht);
}

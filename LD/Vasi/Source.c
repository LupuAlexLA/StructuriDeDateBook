#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Telefon Telefon;
typedef struct Nod Nod;
typedef struct LD LD;

struct Telefon {
	char* denumire;
	int pret;
};

struct Nod {
	Telefon info;
	Nod* prev;
	Nod* next;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

Telefon initializareTelefon(char* denumire, int pret) {
	Telefon t;
	t.denumire = (char*)malloc(sizeof(char*) * (strlen(denumire) + 1));
	strcpy(t.denumire, denumire);
	t.pret = pret;
	return t;
}

void afisareTelefon(Telefon t) {
	printf("Telefonul %s costa %d. \n", t.denumire, t.pret);
}

void inserareInceput(LD* lista, Telefon t) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = NULL;
	nou->next = lista->prim;
	nou->info = t;

	if (lista->prim) {
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void inserareFinal(LD* lista, Telefon  t) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = lista->ultim;
	nou->next = NULL;
	nou->info = t;

	if (lista->ultim) {
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->ultim = nou;
		lista->prim = nou;
	}
}

void afisareStangaDreapta(LD lista) {
	while (lista.prim) {
		afisareTelefon(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void afisareListaCirculara(LD lista) {
	while (lista.prim != lista.ultim) {
		afisareTelefon(lista.prim->info);
		lista.prim = lista.prim->next;
	}
	afisareTelefon(lista.prim->info);
}

void dezalocare(LD* lista) {
	Nod* aux;
	aux = lista->ultim;
	while (aux) {
		free(aux->info.denumire);
		aux = aux->prev;
		if (aux) {
			free(aux->next);
		}
	}
	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void conversieListaInVector(Telefon** vector, LD lista, int* poz) {
	while (lista.prim) {
		(*vector)[*poz] = initializareTelefon(lista.prim->info.denumire, lista.prim->info.pret);
		(*poz)++;
		lista.prim = lista.prim->next;
	}
}

void main() {
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, initializareTelefon("Samsung", 1500));
	inserareInceput(&lista, initializareTelefon("Huawe", 1300));
	inserareInceput(&lista, initializareTelefon("iPhone", 2500));

	inserareFinal(&lista, initializareTelefon("Chinezarie", 600));
	inserareFinal(&lista, initializareTelefon("AllView", 300));

	printf("Afisare lista dubla\n");
	afisareStangaDreapta(lista);

	/*lista.prim->prev = lista.ultim;
	lista.ultim->next = lista.prim;
	printf("\nAfisare lista circulara\n");
	afisareListaCirculara(lista);*/

	int nr_telefoane = 5;
	Telefon* vector = (Telefon*)malloc(sizeof(Telefon) * nr_telefoane);
	int poz = 0;
	conversieListaInVector(&vector, lista, &poz);
	printf("\nAfisare vector\n");
	for (int i = 0; i < poz; i++) {
		afisareTelefon(vector[i]);
		free(vector[i].denumire);
	}
	free(vector);

	dezalocare(&lista);
}

// TEMA
// 1. afisare dreapta-stanga
// 2. de calculat numarul de telefoane din lista

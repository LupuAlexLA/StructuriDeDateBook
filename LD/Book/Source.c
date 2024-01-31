#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h> 
#include <stdlib.h>
#define DIM 100
#define LINE_BUFFER 128

typedef struct Telefon Telefon;
typedef struct Nod Nod;

struct Telefon {
	char* nume;
	double pret;
};

struct Nod {
	Telefon* telefon;
	Nod* next;
	Nod* prev;
};

Telefon* creareTelefon(const char* nume, double pret) {
	Telefon* telefon = NULL;

	telefon = (Telefon*)malloc(sizeof(Telefon));
	telefon->nume = (char*)malloc(strlen(nume) + 1);

	strcpy(telefon->nume, nume);
	telefon->pret = pret;

	return telefon;
}

Nod* creareNod(Telefon* telefon) {
	Nod* nod = NULL;
	nod = (Nod*)malloc(sizeof(Nod));
	nod->next = NULL;
	nod->prev = NULL;
	nod->telefon = telefon;
	return nod;
}

void dezalocareNod(Nod* nod) {
	free(nod->telefon->nume);
	free(nod->telefon);
	free(nod);
}

// operatia 1
Nod* inserareLaInceput(Nod* lista, Telefon* telefon) {
	Nod* nod = creareNod(telefon);
	nod->next = lista;
	if (lista) {
		lista->prev = nod;
	}
	return nod;
}

// operatia 2
void inserareLaSfarsit(Nod** lista, Telefon* telefon) {
	Nod* nod = creareNod(telefon);
	if (*lista == NULL) {
		*lista = nod;
	}
	else {
		Nod* aux = *lista;
		while (aux->next) {
			aux = aux->next;
		}
		nod->prev = aux;
		aux->next = nod;
	}
}

// operatia 3.1
void afisareListaDubla(Nod* lista) {
	while (lista) {
		printf("Adresa Nod Curent: %p, InfoUtil: Nume Telefon: %s, Pret: %.2f, Adresa Nod Prev: %p, Adresa Nod Next: %p\n",
			lista, lista->telefon->nume, lista->telefon->pret, lista->prev, lista->next);
		lista = lista->next;
	}
}

// operatia 3.2
void afisareListaCirculara(Nod* lista) {
	Nod* index = lista;
	if (lista->telefon) {
		do {
			printf("Adresa Nod Curent: %p, InfoUtil: Nume Telefon: %s, Pret: %.2f, Adresa Nod Prev: %p, Adresa Nod Next: %p\n",
				index, index->telefon->nume, index->telefon->pret, index->prev, index->next);
			index = index->next;
		} while (index != lista);
	}
}

// operatia 4
Nod* transformaListaToCirculara(Nod* lista) {
	if (lista) {
		Nod* aux = lista;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = lista;
		lista->prev = aux;
	}
	return lista;
}

// operatia 5
void stergerePrimulNodLC(Nod** lista) {
	if ((*lista)->next != *lista) {
		Nod* tmp = *lista;
		*lista = (*lista)->next;
		(*lista)->prev = tmp->prev;
		(*lista)->prev->next = *lista;
		dezalocareNod(tmp);
	}
	else {
		dezalocareNod(*lista);
		*lista = NULL;
	}
}

// operatia 6
void stergereListaCirculara(Nod** lista) {
	while (*lista) {
		stergerePrimulNodLC(lista);
	}
}

void main() {
	FILE* f = fopen("Telefoane.txt", "r");
	Nod* listaPrincipala = NULL, * listaCirculara = NULL;
	Telefon* telefon = NULL;
	char* token, sep_list[] = ",\n", file_line_buf[LINE_BUFFER], * nume = NULL;
	double pret;
	
	if (f) {
		while (fgets(file_line_buf, sizeof(file_line_buf), f)) {
			// citire nume
			token = strtok(file_line_buf, sep_list); 
			nume = (char*)malloc((strlen(token) + 1) * sizeof(char)); 
			strcpy(nume, token); 
			// citire salariu
			token = strtok(NULL, sep_list); 
			pret = atof(token); 
			// creare informatie utila
			telefon = creareTelefon(nume, pret); 
			// operatia 1
			listaPrincipala = inserareLaInceput(listaPrincipala, telefon);
			// operatia 2
			//inserareLaSfarsit(&listaPrincipala, telefon);
		}
		fclose(f);
	}

	// operatia 3.1
	printf("\nOperatia 3.1\nAfisare lista dubla\n");
	afisareListaDubla(listaPrincipala);

	// operatia 4
	listaCirculara = transformaListaToCirculara(listaPrincipala);
	printf("\nOperatia 4\nAfisare lista dupa tranfsormare in lista circulara\n");
	// operatia 3.2
	afisareListaCirculara(listaCirculara);

	// operatia 5
	stergerePrimulNodLC(&listaCirculara);
	printf("\nOperatia 5\nAfisare lista dupa stergerea primului element\n");
	afisareListaCirculara(listaCirculara);

	// operatia 6
	stergereListaCirculara(&listaCirculara);
	printf("\nOperatia 6\nAfisare lista dupa stergerea elementelor\n");
	afisareListaCirculara(&listaCirculara);
}

// aka sem 4 vasi

// Operatii:
// 01. initializare
// 02. afisare
// 1. inserare la inceput
// 2. afisare lista
// 3. inserare la sfarsit
// 4. dezalocare
// 5. calcul medie

#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>
typedef struct Telefon Telefon;
typedef struct Nod Nod;

struct Telefon {
	char* denumire;
	int codTelefon;
	float pret;
};

struct Nod {
	Telefon info;
	Nod* next;
};

void afisareTelefon(Telefon t) {
	printf("\n Telefonul %s are codul %d si pretul %f", t.denumire, t.codTelefon, t.pret);
}

Telefon initializareTelefon(const char* denumire, int codTelefon, float pret) {
	Telefon t;
	t.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(t.denumire, denumire);
	t.codTelefon = codTelefon;
	t.pret = pret;
	return t;
}

void inserareLaInceput(Telefon t, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->next = *cap;
	*cap = nou;
}

void inserareLaSfarsit(Telefon t, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->next = NULL;
	if (*cap)
	{
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		*cap = nou;
	}
}

void afisareLista(Nod* cap) {
	while (cap) {
		afisareTelefon(cap->info);
		cap = cap->next;
	}
}

float calculPretMediu(Nod* cap) {
	float x = 0;
	int contor = 0;
	while (cap) {
		x += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	return contor != 0 ? x / contor : 0;
}

void dezalocare(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.denumire);
		Nod* temp = *cap;
		(*cap) = (*cap)->next;
		free(temp);
	}
}

void main() {
	Nod* cap = NULL;

	inserareLaInceput(initializareTelefon("AllView", 001, 200), &cap);
	inserareLaInceput(initializareTelefon("Nokia", 002, 250), &cap);
	inserareLaInceput(initializareTelefon("Samsung1", 003, 300), &cap);

	inserareLaSfarsit(initializareTelefon("Chinezarie", 004, 600), &cap);
	inserareLaSfarsit(initializareTelefon("Samsung2", 005, 800), &cap);
	inserareLaSfarsit(initializareTelefon("LG", 006, 0), &cap);

	afisareLista(cap);

	float mediu = calculPretMediu(cap);
	printf("\nPretul mediu = %f", mediu);

	dezalocare(&cap);
	afisareLista(cap);
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Telefon Telefon;
typedef struct Nod Nod;

struct Telefon {
	long id;
	char* nume;
	int pret;
};

struct Nod {
	Nod* next;
	Telefon inf;
};

Telefon initializareTelefon(long id, char* nume, int pret) {
	Telefon t;
	t.id = id;
	t.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(t.nume, nume);
	t.pret = pret;
	return t;
}

void afisareTelefon(Telefon t) {
	printf("\nTelefonul cu id-ul %ld se numeste %s si costa %d\n", t.id, t.nume, t.pret);
}

// Stiva
Nod* push(Nod* varf, Telefon telefon) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = telefon;
	nou->next = varf;
	return nou;
}

Telefon pop(Nod** varf) {
	Telefon telefon;
	if (*varf != NULL) {
		telefon = (*varf)->inf;
		Nod* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}
	else {
		telefon.id = -1;
		telefon.nume = NULL;
		telefon.pret = 0;
	}
	return telefon;
}

Telefon cautaTelefon(long id, Nod** varf) {
	Telefon telefon;
	telefon.id = -1; 
	telefon.nume = NULL; 
	telefon.pret = 0; 

	Nod* stivaAux = NULL;
	while (*varf != NULL && (*varf)->inf.id != id) {
		stivaAux = push(stivaAux, pop(varf));
	}
	if (*varf != NULL) {
		telefon = pop(varf);
	}
	while (stivaAux != NULL) {
		*varf = push(*varf, pop(&stivaAux));
	}
	return telefon;
} 

// Coada
void put(Nod** prim, Telefon telefon) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = telefon;
	nou->next = NULL;
	Nod* aux = (*prim);
	if (aux) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*prim) = nou;
	}
}

Telefon cautaSiExtrageDinCoada(long id, Nod** coada) {
	Nod* coadaTemp = NULL;
	Telefon telefonGasit;
	telefonGasit.id = -1;
	telefonGasit.nume = NULL;
	telefonGasit.pret = 0;

	while (*coada) {
		Telefon telefonCurent = pop(coada);
		if (telefonCurent.id == id) {
			telefonGasit = telefonCurent;
			break;
		}
		else {
			put(&coadaTemp, telefonCurent);
		}
	}

	while (coadaTemp) {
		put(coada, pop(&coadaTemp));
	}

	return telefonGasit;
}

void main() {
	Nod* varf = NULL;

	varf = push(varf, initializareTelefon(1, "Samsung", 2000));
	varf = push(varf, initializareTelefon(2, "iPhone", 3000));
	varf = push(varf, initializareTelefon(3, "Pixel", 2500));

	printf("Cautare telefon cu id 2\n");
	afisareTelefon(cautaTelefon(2, &varf));

	printf("Afisare stiva\n");
	while (varf) {
		Telefon telefon = pop(&varf);
		afisareTelefon(telefon);
		free(telefon.nume);
	}

	Nod* coada = NULL;

	put(&coada, initializareTelefon(4, "Huawei", 1500));
	put(&coada, initializareTelefon(5, "BlackBerry", 1000));
	put(&coada, initializareTelefon(6, "OnePro", 1000));

	printf("Cautare telefon cu id 5\n");
	long idCautat = 5;
	Telefon telefonGasit = cautaSiExtrageDinCoada(idCautat, &coada);
	if (telefonGasit.id != -1) {
		printf("Telefon gasit:\n");
		afisareTelefon(telefonGasit);
		free(telefonGasit.nume);
	}
	else {
		printf("Telefonul cu id-ul %ld nu a fost gasit.\n", idCautat);
	}

	printf("\n\nAfisare coada:");
	while (coada) {
		Telefon telefon = pop(&coada);
		afisareTelefon(telefon);
		free(telefon.nume);
	}
	

}

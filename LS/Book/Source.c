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
	nod->telefon = telefon;
	return nod;
}

void dezalocareNod(Nod* nod) {
	free(nod->telefon->nume);
	free(nod->telefon);
	free(nod);
}

// operatia 1
Nod* inserareInceputLista(Nod* lista, Telefon* telefon) {
	Nod* nod = creareNod(telefon);
	nod->next = lista;
	return nod;
}

// operatia 2
void inserareNodPozitieLista(Nod** lista, Telefon* telefon, int poz) {
	Nod* aux = *lista;
	int index = 1;
	if (poz == 1) {
		*lista = inserareInceputLista(*lista, telefon);
	}
	else if (poz > 1) {
		while (aux && index++ < poz - 1) {
			aux = aux->next;
		}
		if (aux) {
			aux->next = inserareInceputLista(aux->next, telefon);
		}
	}
}

// operatia 3
int calculNumarNoduriLista(Nod* lista) {
	int nrNoduri = 0;
	while (lista != NULL) {
		nrNoduri++;
		lista = lista->next;
	}
	return nrNoduri;
}

// operatia 4
void afisareLista(Nod* lista) {
	while (lista) {
		printf("Adresa Nod Curent: %p, InfoUtil: Nume telefon: %s, pret: %.2f, Adresa Nod Next: %p\n",
			&*lista, lista->telefon->nume, lista->telefon->pret, lista->next);
		lista = lista->next;
	}
}

// operatia 5.1
Telefon* accesNodPozitieKLista(Nod* lista, int poz) {
	Telefon* element = NULL;
	if (poz >= 1) {
		int index = 1;
		while (lista && index++ < poz) {
			lista = lista->next;
		}
		if (lista) {
			element = lista->telefon;
		}
		return element;
	}
}

// operatia 5.2
Telefon* cautareNodAngajatNumeLista(Nod* lista, const char* nume) {
	Telefon* element = NULL;
	while (lista && strcmp(lista->telefon->nume, nume) != 0) {
		lista = lista->next;
	}
	if (lista) {
		element = lista->telefon;
	}
	return element;
}

// operatia 6
int calculPreturiPestePragLista(Nod* lista, double prag) {
	int rezultat = 0;
	while (lista) {
		if (lista->telefon->pret > prag) {
			rezultat++;
		}
		lista = lista->next;
	}
	return rezultat;
}

// operatia 7
Nod* stergereNodPozitieLista(Nod* lista, int poz) {
	int index = 1;
	Nod* aux = NULL;
	if (poz == 1) {
		aux = lista; 
		lista = lista->next;
	}
	else if (poz > 1) {
		Nod* ptrIndex = lista;
		while (ptrIndex && index++ < poz - 1) {
			ptrIndex = ptrIndex->next;
		}
		if (ptrIndex && ptrIndex->next) {
			aux = ptrIndex->next;
			ptrIndex->next = aux->next;
		}
	}
	if (aux) {
		free(aux->telefon->nume);
		free(aux->telefon);
		free(aux);
	}
	return lista;
}

// operatia 8
Nod* separareListeDupaPozitie(Nod** listaPrincipala, int poz) {
	Nod* aux = NULL, * listaSecundara = NULL;
	int index = 1;
	if (poz == 1) {
		listaSecundara = (*listaPrincipala)->next;
		(*listaPrincipala)->next = NULL;
	}
	else if (poz > 1) {
		aux = *listaPrincipala;
		while (aux && index++ < poz) {
			aux = aux->next;
		}
	}
	if (aux) {
		listaSecundara = aux->next;
		aux->next = NULL;
	}
	return listaSecundara;
}

// operatia 9
Nod* concatenareListe(Nod* l1, Nod* l2) {
	Nod* aux = l1;
	while (aux->next) {
		aux = aux->next;
	}
	aux->next = l2;
	return l1;
}

// operatia 10
void sortareListaPretTelefon(Nod* lista) {
	for (Nod* pAux = lista; pAux; pAux = pAux->next) {
		for (Nod* sAux = pAux; sAux; sAux = sAux->next) {
			if (pAux->telefon->pret > sAux->telefon->pret) {
				Telefon* tmp = pAux->telefon;
				pAux->telefon = sAux->telefon;
				sAux->telefon = tmp;
			}
		}
	}
}

// operatia 11
Nod* stergereLista(Nod* lista) {
	while (lista) {
		Nod* tmp = lista;
		lista = lista->next;
		dezalocareNod(tmp);
	}
	return NULL;
}

void main() {
	FILE* f = fopen("Telefoane.txt", "r");
	Nod* listaPrincipala = NULL; // cap la Vasi
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
			listaPrincipala = inserareInceputLista(listaPrincipala, telefon);
		}
		fclose(f);
	}

	// operatia 2
	Telefon* t1 = creareTelefon("Huawei", 1500);
	inserareNodPozitieLista(&listaPrincipala, t1, 7);

	// operatia 3
	int nrNoduri = calculNumarNoduriLista(listaPrincipala);
	printf("\nOperatia 3\nNumarul de noduri din lista: %d\n", nrNoduri);

	// operatia 4
	printf("\nOperatia 4\nAfisare continut lista:\n");
	afisareLista(listaPrincipala);

	// operatia 5.1
	int poz = 7;
	Telefon* t2 = accesNodPozitieKLista(listaPrincipala, poz);
	if (t2 != NULL) {
		printf("\nOperatia 5.1\nNod pozitie %d: InfoUtil: Nume telefon: %s, pret: %.2f\n", 
			poz, t2->nume, t2->pret);
	}
	else {
		printf("\nOperatia 5.1\nNodul de pe pozitia %d nu exista!\n", poz);
	}

	// operatia 5.2
	const char* value = "Samsung";
	Telefon* t3 = cautareNodAngajatNumeLista(listaPrincipala, value);
	if (t3 != NULL) {
		printf("\nOperatia 5.2\nInfoUtil: Nume telefon: %s, pret: %.2f\n", 
			t3->nume, t3->pret);
	}
	else {
		printf("\nOperatia 5.2\nTelefonul cu numele %s nu exista!\n", value);
	}
	
	// operatia 6
	double prag = 500.0;
	int nrPreturi = calculPreturiPestePragLista(listaPrincipala, prag);
	printf("\nOperatia 6\nSunt %d telefoane care au pretul peste pragul %.2f\n", 
		nrPreturi, prag);

	// operatia 7
	poz = 6;
	listaPrincipala = stergereNodPozitieLista(listaPrincipala, poz);
	printf("\nOperatia 7\nAfisare lista dupa stergere nod pozitia %d: \n", poz);
	afisareLista(listaPrincipala);

	// operatia 8
	poz = 4;
	Nod* listaSecundara = NULL;
	listaSecundara = separareListeDupaPozitie(&listaPrincipala, poz);
	printf("\nOperatia 8\nAfisare lista principala dupa separare de la nod pozitia %d: \n", poz);
	afisareLista(listaPrincipala);
	printf("\nAfisare lista secundara dupa separare de la nod pozitia %d: \n", poz);
	afisareLista(listaSecundara);

	// operatia 9
	listaPrincipala = concatenareListe(listaPrincipala, listaSecundara);
	printf("\nOperatia 9\nAfisare lista concatenata:\n");
	afisareLista(listaPrincipala);

	// operatia 10
	sortareListaPretTelefon(listaPrincipala);
	printf("\nOperatia 10\nAfisare lista sortata dupa pret:\n");
	afisareLista(listaPrincipala);

	// operatia 11
	listaPrincipala = stergereLista(listaPrincipala);
	printf("\nOperatia 11\nAfisare lista dupa stergere:\n");
	afisareLista(listaPrincipala);
}

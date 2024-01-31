#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define DIM 100
#define LINESIZE 128

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	int id;
	char* nume;
	char nrCai[4];
};

struct Nod {
	Masina masina;
	Nod* next;
};

struct Nod* inserareLista(Nod* prim, Masina m) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->masina.id = m.id;
	nou->masina.nume = (char*)malloc(sizeof(char) * (strlen(m.nume) + 1));
	strcpy(nou->masina.nume, m.nume);
	strcpy(nou->masina.nrCai, m.nrCai);
	nou->next = prim;
	return nou;
}

unsigned int functieHash(char* nume_masina, int sizeHT) {
	unsigned int temp = 0, poz; // suma valorilor ASCII
	for (unsigned int i = 0; i < strlen(nume_masina); i++) {
		temp += nume_masina[i];
	}
	poz = temp % sizeHT;
	return poz;
}

void inserareHTable(Nod** hTab, Masina m, int sizeHT) {
	int k; // pozitie de inserare pentru datele masinii m
	k = functieHash(m.nume, sizeHT); // calcul valoare functie hash
	hTab[k] = inserareLista(hTab[k], m);
}

parseHTable(Nod** hTab, int sizeHT) {
	for (int i = 0; i < sizeHT; i++) {
		if (hTab[i]) {
			// lista i contine cel putin o masina
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->masina.id, tmp->masina.nume);
				tmp = tmp->next;
			}
		}
	}
}

Masina cautare_tabela_hash(Nod** hTab, char* nume_masina, int sizeHT) {
	int k;
	k = functieHash(nume_masina, sizeHT);
	Masina m;
	m.nume = NULL;
	Nod* tmp = hTab[k];
	while (tmp) {
		// cautare secventiala a setului de date
		if ((m.nume == NULL) && strcmp(nume_masina, tmp->masina.nume) == 0) {
			m.id = tmp->masina.id;
			m.nume = (char*)malloc(sizeof(char) * (strlen(tmp->masina.nume) + 1));
			strcpy(m.nume, tmp->masina.nume);
			strcpy(m.nrCai, tmp->masina.nrCai);
		}
		tmp = tmp->next;
	}
	return m;
}

Nod* stergere_masini_nume(Nod** hTab, char* nume_masina, int sizeHT) {
	int k;
	Nod* lst_masini = NULL;
	k = functieHash(nume_masina, sizeHT);
	Nod* tmp = hTab[k];
	Nod* tmp_prev = NULL;
	while (tmp) {
		if (strcmp(nume_masina, tmp->masina.nume) == 0) { // masina de sters este in nodul tmp
			if (hTab[k] == tmp) {
				// masina eliminata este in primul nod al listei hTab[k]
				hTab[k] = tmp->next;
				tmp->next = lst_masini;
				lst_masini = tmp;
				tmp = hTab[k];
			}
			else {
				// nodul de sters e tmp
				tmp_prev->next = tmp->next; // izolare tmp din lista hTab[k]
				// adaugarea nodului tmp in lista simpla rezultat pe prima poz
				tmp->next = lst_masini;
				lst_masini = tmp;
				tmp = tmp_prev->next; // urmatorul nod de verificat
				// masinile de sters pot fi plasate in noduri consecutive in cadrul listei hTab[k]
			}
		}
		else {
			tmp_prev = tmp;
			tmp = tmp->next;
		}
	}
	return lst_masini;
}

unsigned int* liste_max_coliziuni(Nod** hTab, int sizeHT, unsigned int* n_list, unsigned int* max_elem) {
	unsigned int* v_max = NULL, k, nr_masini, i;
	*n_list = 0; // numar liste cu numar maxim de noduri/elemente/masini
	*max_elem = 0; // lista cu maxim 0 noduri corespuinde unei tabele hash empty
	// se traverseaza intreaga tabela de dispersie
	for (int i = 0; i < (unsigned int)sizeHT; i++) {
		if (hTab[i]) {
			// exista lista i in tabela hTab
			nr_masini = 0;
			Nod* tmp = hTab[i];
			while (tmp)
			{
				nr_masini += 1;
				tmp = tmp->next;
			}
			if (nr_masini > (*max_elem)) {
				*max_elem = nr_masini;
				*n_list = 1;
			}
			else {
				if (nr_masini == (*max_elem)) {
					*n_list += 1;
				}
			}
		}
	}
	// alocare vector pentru retinere indecsi de liste de coliziune cu nr maxim de studenti
	v_max = malloc((*n_list) * sizeof(unsigned int));
	k = 0;
	for (i = 0; i < (unsigned int)sizeHT; i++) {
		if (hTab[i]) {
			nr_masini = 0;
			Nod* tmp = hTab[i];
			while (tmp) {
				nr_masini += 1;
				tmp = tmp->next;
			}
			if (nr_masini == (*max_elem))
			{
				v_max[k] = i + 1;
				k += 1;
			}
		}
	}
	return v_max;
}

int main() {
	// vector cu elemente de tip adresa (inceput de lista simpla cu masini 
	// care colizionizeaza pe cheia de cautare utilizata)
	Nod** HTable; 
	Masina masina;

	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i < DIM; i++) {
		HTable[i] = NULL; // HTable[i] => elementul i din tabela hash
	}

	FILE* f = fopen("Masini.txt", "r");
	char* token, file_line_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_line_buf, sizeof(file_line_buf), f)) {
		token = strtok(file_line_buf, sep_list);
		masina.id = atoi(token);

		token = strtok(NULL, sep_list);
		masina.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(masina.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(masina.nrCai, token);

		token = strtok(NULL, sep_list);
		if (token) {
			printf("\nEroare preluare token!");
		}

		// inserare Masina in tabela de dispersie
		inserareHTable(HTable, masina, DIM);
		printf("Masina %s inserata \n", masina.nume);
	}
	fclose(f);

	// verificare vizuala a continutului structurii tabela de dispersie
	printf("\nTabela de dispersie dupa creare si populare:\n");
	parseHTable(HTable, DIM);

	masina = cautare_tabela_hash(HTable, (char*)"Porsche 911", DIM);

	if (masina.nume != NULL) {
		printf("Masina identificata: %d %s\n\n", masina.id, masina.nrCai);
		free(masina.nume);
	}
	else {
		printf("Masina nu a fost identificata in tabela de dispersie.\n\n");
	}

	// determinare lista simpla cu maximul de coliziuni in tabela de dispersie
	unsigned int n_liste, max_masini, * v_liste_max = NULL;
	v_liste_max = liste_max_coliziuni(HTable, DIM, &n_liste, &max_masini);
	if (max_masini == 0) {
		printf("\nTabela de dispersie empty.\n");
	}
	else {
		printf("\n\nMaximul de coliziuni este %u, prezent in urmatoarele liste: ", max_masini);
		for (unsigned int i = 0; i < n_liste; i++) {
			printf(" %u ", v_liste_max[i]);
		}
	}

	// stergere masini pe baza cheii de cautare "nume masina"
	Nod* lst_masini_eliminate = stergere_masini_nume(HTable, (char*)"Nissan GT-R", DIM);
	printf("\n\nSeturi de date eliminate din tabela de dispersie:");
	if (lst_masini_eliminate != 0) {
		Nod* t = lst_masini_eliminate;
		while (t) {
			printf("\n ---Masina eliminata din tabela de dispersie: %d %s, nr cai %s",
				t->masina.id, t->masina.nume, t->masina.nrCai);
			t = t->next;
		}
	}
	else {
		printf("\n\n ---Nu au fost identificate masini pentru cheia de cautare specificata.\n");
	}

	// verificare vizuala a continutului structurii tabela de dispersie dupa eliminare masini
	printf("\n\nTabela de dispersie dupa stergere studenti pe baza cheii de cautare:\n");
	parseHTable(HTable, DIM);

	// dezalocarea tabelei de dispersie
	for (int i = 0; i < DIM; i++) {
		// dezalocare liste
		if (HTable[i] != NULL) {
			// lista i contine cel putin o masina
			Nod* tmp = HTable[i];
			while (tmp) {
				HTable[i] = HTable[i]->next; // mutare inceput de liste pe nodul 2
				free(tmp->masina.nume); // dezalocare nume masina din nodul 1
				free(tmp); // dezalocare nod 1
				tmp = HTable[i]; // noul inceput de lista care se va dezaloca pe iteratia urm
			}
		}
	}
	free(HTable); // dezalocare vector suport pentru tabela de dispersie
	HTable = NULL;

	// dezalocare lista masini creata la operatia de stergere element in tabela de dispersie
	while (lst_masini_eliminate) {
		Nod* t = lst_masini_eliminate;
		lst_masini_eliminate = lst_masini_eliminate->next;
		free(t->masina.nume);
		free(t);
	}

	// dezalocare vector indecsi liste cu nr maxim de studenti in tabela de dispersie
	free(v_liste_max);
	v_liste_max = NULL;

	return 0;
}

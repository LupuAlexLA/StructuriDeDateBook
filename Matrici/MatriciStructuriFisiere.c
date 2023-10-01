// Secventa de cod de mai os imparte un vector de carti in trei categorii.
// Cele trei categorii vor fi salvate pe trei linii ale unei matrici.
// Pentru stabilirea celor trei intervale este folosit pretul cartilor.
// Este stabilit pretul minim, pretul maxim, oar cele trei intervale
// vor fi realizate in mod egal pentru intervalele de preturi.

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Carte {
	char* titluCarte;
	int numarCapitole;
	char** titluriCapitole;
	int numarPagini;
	float pretCarte;
} typedef Carte;

Carte copiazaCarte(Carte carteVeche) {
	Carte carte;
	carte.titluCarte = (char*)malloc(sizeof(char) * (strlen(carteVeche.titluCarte) + 1));
	strcpy(carte.titluCarte, carteVeche.titluCarte);
	carte.numarCapitole = carteVeche.numarCapitole;
	carte.titluriCapitole = (char**)malloc(sizeof(char*) * carte.numarCapitole);
	for (int i = 0; i < carte.numarCapitole; i++) {
		carte.titluriCapitole[i] = (char*)malloc(sizeof(char) * (strlen(carteVeche.titluriCapitole[i]) + 1));
		strcpy(carte.titluriCapitole[i], carteVeche.titluriCapitole[i]);
	}
	carte.numarPagini = carteVeche.numarPagini;
	carte.pretCarte = carteVeche.pretCarte;

	return carte;
}

Carte citesteCarte(FILE* f) {
	struct Carte c;
	char buffer[50];

	fgets(buffer, 50, f);
	char* token;
	token = strtok(buffer, "\n");
	c.titluCarte = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(c.titluCarte, token);

	fgets(buffer, 50, f);
	c.numarCapitole = atoi(buffer);

	c.titluriCapitole = (char**)malloc(sizeof(char*) * c.numarCapitole);
	for (int i = 0; i < c.numarCapitole; i++) {
		fgets(buffer, 50, f);
		token = strtok(buffer, "\n");
		c.titluriCapitole[i] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(c.titluriCapitole[i], token);
	}

	fgets(buffer, 50, f);
	c.numarPagini = atoi(buffer);

	fgets(buffer, 50, f);
	c.pretCarte = atof(buffer);

	return c;
}

void afiseazaCarte(Carte carte) {
	printf("Cartea %s are %d capitole:\n", carte.titluCarte, carte.numarCapitole);
	for (int i = 0; i < carte.numarCapitole; i++) {
		printf("%s; ", carte.titluriCapitole[i]);
	}
	printf("\nAceasta are %d pagini si costa %5.2f RON.\n", carte.numarPagini, carte.pretCarte);
}

Carte* citesteVectorCartiDinFisier(const char* numeFisier, int* nrCarti) {
	FILE* f = fopen(numeFisier, "r");
	struct Carte* vector = NULL;
	if (f != NULL) {
		char buffer[10];
		fgets(buffer, 10, f);
		*nrCarti = atoi(buffer);
	}
	if (nrCarti > 0) {
		vector = (struct Carte*)malloc(sizeof(struct Carte) * (*nrCarti));
		int index = 0;
		while (!feof(f)) {
			vector[index] = citesteCarte(f);
			index = index + 1;
		}
		fclose(f);
		return(vector);
	}
}

void afiseazaVectorCarti(Carte* vector, int nrCarti) {
	for (int i = 0; i < nrCarti; i++) {
		afiseazaCarte(vector[i]);
		printf("\n");
	}
}

void stergereMemorieVector(Carte** vector, int nrCarti) {
	for (int i = 0; i < nrCarti; i++) {
		free((*vector)[i].titluCarte);
		for (int j = 0; j < (*vector)[i].numarCapitole; j++) {
			free((*vector)[i].titluriCapitole[j]);
		}
		free((*vector)[i].titluriCapitole);
	}
	free(*vector);
	*vector = NULL;
}

float cautarePretMinim(Carte* vector, int nrCarti) {
	if (nrCarti > 0) {
		float min = vector[0].pretCarte;
		for (int i = 1; i < nrCarti; i++) {
			if (min > vector[i].pretCarte) {
				min = vector[i].pretCarte;
			}
		}
		return min;
	}
	return 0;
}

float cautarePretMaxim(Carte* vector, int nrCarti) {
	if (nrCarti > 0) {
		float max = vector[0].pretCarte;
		for (int i = 1; i < nrCarti; i++) {
			if (max < vector[i].pretCarte) {
				max = vector[i].pretCarte;
			}
		}
		return max;
	}
	return 0;
}

Carte** creareMatriceCuTreiIntervalePret(Carte* vector, int nrCarti, int* nrLinii, int** nrElementeLinie) {
	float pretMinim = cautarePretMinim(vector, nrCarti);
	float pretMaxim = cautarePretMaxim(vector, nrCarti);
	*nrLinii = 3;

	*nrElementeLinie = (int*)malloc(sizeof(int) * (*nrLinii));
	Carte** matrice = (Carte**)malloc(sizeof(Carte*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++) {
		(*nrElementeLinie)[i] = 0;
		matrice[i] = NULL;
	}

	float prag1 = pretMinim + (pretMaxim - pretMinim) / 3;
	float prag2 = prag1 + (pretMaxim - pretMinim) / 3;
	// pret < prag1 ==> pozitia 0
	// pret >= prag1 && pret < prag2 ==> pozitia 1
	// pret > prag2 ==> pozitia 2
	for (int i = 0; i < nrCarti; i++) {
		int pozitie = 0;
		if (vector[i].pretCarte < prag1) {
			pozitie = 0;
		}
		else if (vector[i].pretCarte >= prag1 && vector[i].pretCarte < prag2) {
			pozitie = 1;
		}
		else {
			pozitie = 2;
		}
		Carte* aux = (Carte*)malloc(sizeof(Carte) * ((*nrElementeLinie)[pozitie] + 1));
		if (matrice[pozitie] != NULL) {
			for (int i = 0; i < (*nrElementeLinie)[pozitie]; i++) {
				aux[i] = matrice[pozitie][i]; // shallow copy
			}
			free(matrice[pozitie]);
		}
		aux[(*nrElementeLinie)[pozitie]] = copiazaCarte(vector[i]); // deep copy

		matrice[pozitie] = aux; // deep copy
		((*nrElementeLinie)[pozitie])++;
	}
	return matrice;
}

void afisareMatrice(int nrLinii, int* nrElementeLinie, Carte** matrice) {
	for (int i = 0; i < nrLinii; i++) {
		printf("Linia %d : \n", (i + 1));
		for (int j = 0; j < nrElementeLinie[i]; j++) {
			afiseazaCarte(matrice[i][j]);
		}
		printf("\n");
	}
}

void dezalocareMemorieMatrice(Carte*** matrice, int* nrLinii, int** nrElementeLinie) {
	for (int i = 0; i < *nrLinii; i++) {
		for (int j = 0; j < (*nrElementeLinie)[i]; j++) {
			free((*matrice)[i][j].titluCarte);
			for (int k = 0; k < ((*matrice)[i][j]).numarCapitole; k++) {
				free(((*matrice)[i][j]).titluriCapitole[k]);
			}
			if (((*matrice)[i][j]).titluriCapitole) {
				free(((*matrice)[i][j]).titluriCapitole);
			}
		}
		if ((*matrice)[i]) {
			free((*matrice)[i]);
		}
	}
	free(*nrElementeLinie);
	free(*matrice);
	*matrice = NULL;
	*nrElementeLinie = NULL;
	*nrLinii = 0;
}

void mutaCartePeAltaLinie(Carte** matrice, int nrLinii, int* nrElementeLinie, int linieSursa, int linieDestinatie) {
	Carte* aux = (Carte*)malloc((nrElementeLinie[linieDestinatie] + 1) * sizeof(Carte));
	for (int i = 0; i < nrElementeLinie[linieDestinatie]; i++) {
		aux[i] = matrice[linieDestinatie][i];
	}
	aux[nrElementeLinie[linieDestinatie]] = matrice[linieSursa][nrElementeLinie[linieSursa] - 1];

	free(matrice[linieDestinatie]);
	matrice[linieDestinatie] = aux;
	if (nrElementeLinie[linieSursa] > 1) {
		aux = (Carte*)malloc(((nrElementeLinie[linieSursa]) - 1) * sizeof(Carte));
		for (int i = 0; i < nrElementeLinie[linieSursa] - 1; i++) {
			aux[i] = matrice[linieSursa][i];
		}
		free(matrice[linieSursa]);
		matrice[linieSursa] = aux;
	}
	else {
		free(matrice[linieSursa]);
		matrice[linieSursa] = NULL;
	}
	nrElementeLinie[linieDestinatie]++;
	nrElementeLinie[linieSursa]--;
}

float calculeazaPretulTotal(Carte* carti, int nrCarti) {
	float pretTotal = 0;
	for (int i = 0; i < nrCarti; i++) {
		pretTotal += carti[i].pretCarte;
	}
	return pretTotal;
}

float* calcularePreturiMediiPeLinii(Carte** matrice, int nrLinii, int* nrElementeLinie) {
	float* preturiMedii = (float*)malloc(nrLinii * sizeof(int));
	for (int i = 0; i < nrLinii; i++) {
		if (nrElementeLinie[i] > 0) {
			preturiMedii[i] = calculeazaPretulTotal(matrice[i], nrElementeLinie[i]) / nrElementeLinie[i];
		}
		else {
			preturiMedii[i] = 0;
		}
	}
	return preturiMedii;
}

// metoda selectiei
void sortareCrescatoareLiniiMatrice(Carte** matrice, int nrLinii, int* nrElementeLinie) {
	for (int i = 0; i < nrLinii - 1; i++) {
		for (int j = i + 1; j < nrLinii; j++) {
			if (nrElementeLinie[i] > nrElementeLinie[j]) {
				int auxInteger = nrElementeLinie[i];
				nrElementeLinie[i] = nrElementeLinie[j];
				nrElementeLinie[j] = auxInteger;
				Carte* auxPointer = matrice[i];
				matrice[i] = matrice[j];
				matrice[j] = auxPointer;
			}
		}
	}
}

void main() {
	int nrCarti = 0;
	Carte* carti = citesteVectorCartiDinFisier("carti.txt", &nrCarti);
	printf("\nToate cartile:\n");
	afiseazaVectorCarti(carti, nrCarti);

	printf("MINIM:%5.2f\n", cautarePretMinim(carti, nrCarti));
	printf("MAXIM:%5.2f\n", cautarePretMaxim(carti, nrCarti));

	int nrLinii = 0;
	int* nrElementeLinie = NULL;
	Carte** matriceCarti = creareMatriceCuTreiIntervalePret(carti, nrCarti, &nrLinii, &nrElementeLinie);
	afisareMatrice(nrLinii, nrElementeLinie, matriceCarti);
	sortareCrescatoareLiniiMatrice(matriceCarti, nrLinii, nrElementeLinie);
	afisareMatrice(nrLinii, nrElementeLinie, matriceCarti);
	float* medii = calcularePreturiMediiPeLinii(matriceCarti, nrLinii, nrElementeLinie);
	printf("Preturi medii: ");
	for (int i = 0; i < nrLinii; i++) {
		printf("%5.2f ", medii[i]);
	}
	mutaCartePeAltaLinie(matriceCarti, nrLinii, nrElementeLinie, 0, 1);
	printf("Interschimbare\n");
	afisareMatrice(nrLinii, nrElementeLinie, matriceCarti);
	
	dezalocareMemorieMatrice(&matriceCarti, &nrLinii, &nrElementeLinie);
	stergereMemorieVector(&carti, nrCarti);
}


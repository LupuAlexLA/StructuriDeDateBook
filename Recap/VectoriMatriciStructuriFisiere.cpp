#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Telefon {
	char* denumire;
	int memorie;
	float pret;
};

void citireVectorDinFisier1(const char* numeFisier, int** v, int* dim) {
	FILE* f = NULL;
	f = fopen(numeFisier, "r");
	if (f != NULL) {
		fscanf(f, "%d", dim);
		*v = (int*)malloc((*dim) * sizeof(int));
		for (int i = 0; i < (*dim); i++) {
			fscanf(f, "%d", (*v) + i);
		}
		fclose(f);
	}
	else {
		printf("Nu s-a putut deschide fisierul");
	}
}

int* citireVectorDinFisier2(const char* numeFisier, int* dimens) {
	FILE* f = fopen(numeFisier, "r");
	int* vector = NULL;

	if (f != NULL) {
		fscanf(f, "%d", dimens);
	}

	if(*dimens > 0) {
		vector = (int*)malloc((*dimens) * sizeof(int));
		int index = 0;
		while (!feof(f)) {
			fscanf(f, "%d", &vector[index]);
			index = index + 1;
		}
	}

	fclose(f);
	return vector;
}

void afisareVector(int* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		printf("%d ", vector[i]);
	}
}

struct Telefon citireDateTelefon(FILE* streamFisier) {
	struct Telefon telefon;

	if (streamFisier != NULL) {
		char buffer[20];
		fgets(buffer, 20, streamFisier);
		char* sir = strtok(buffer, "\n");

		telefon.denumire = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(telefon.denumire, sir);

		fgets(buffer, 7, streamFisier);
		telefon.memorie = atoi(buffer);

		fgets(buffer, 9, streamFisier);
		telefon.pret = atof(buffer);
	}

	return telefon;
}

void afisareTelefon(struct Telefon tel) {
	printf("Nume = %s; Memorie = %d; Pret = %.2f", tel.denumire, tel.memorie, tel.pret);
}

// vers 1 de citire vectorTelefoane
void citireVectorTelefoane1(const char* numeFisier, struct Telefon** telefoane, int* dim) {
	FILE* f = NULL;
	f = fopen(numeFisier, "r");

	if (f != NULL) {
		char buffer[100];
		fgets(buffer, 100, f);
		*dim = atoi(buffer);

		*telefoane = (struct Telefon*)malloc((*dim) * sizeof(struct Telefon));

		for (int i = 0; i < *dim; i++) {
			(*telefoane)[i] = citireDateTelefon(f);
		}
		
		fclose(f);
	}
	else {
		printf("Eroare la deschiderea fisierului!");
	}
}

// vers 2 de citire vectorTelefoane
void citireVectorTelefoane2(FILE* streamFisier, struct Telefon** telefoane, int* dim) {
	

	if (streamFisier != NULL) {
		char buffer[100];
		fgets(buffer, 100, streamFisier);
		*dim = atoi(buffer);

		*telefoane = (struct Telefon*)malloc((*dim) * sizeof(struct Telefon));

		for (int i = 0; i < *dim; i++) {
			(*telefoane)[i] = citireDateTelefon(streamFisier);
		}

		//fclose(streamFisier);
	}
	else {
		printf("Eroare la deschiderea fisierului!");
	}
}

void citireMatrice(const char* numeFisier, struct Telefon*** telefoane, int** dimensiuni, int* nrLinii) {
	FILE* f = NULL;
	f = fopen(numeFisier, "r");

	if (f != NULL) {
		char buffer[50];
		fgets(buffer, 5, f);
		*nrLinii = atoi(buffer);
		*telefoane = (Telefon**)malloc((*nrLinii) * sizeof(Telefon*));
		*dimensiuni = (int*)malloc(sizeof(int) * (*nrLinii));

		for (int i = 0; i < *nrLinii; i++) {
			citireVectorTelefoane2(f, (*telefoane) + i, (*dimensiuni) + i);
		}

		fclose(f);
	}
	else {
		printf("Eroare la deschiderea fisierului!");
	}
}

void afisareMatrice(struct Telefon** matrice, int* dimensiuni, int nrLinii) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < dimensiuni[i]; j++) {
			afisareTelefon(matrice[i][j]);
		}
		printf("\n");
	}
}

void dezalocareMatrice(struct Telefon*** matrice, int** dimensiuni, int* nrLinii) {
	for (int i = 0; i < *nrLinii; i++) {
		for (int j = 0; j < (*dimensiuni)[i]; j++) {
			free((*matrice)[i][j].denumire);
		}
		free((*matrice)[i]);
	}
	free(*matrice);
	free(*dimensiuni);
	*nrLinii = 0;
	*matrice = NULL;
	*dimensiuni = NULL;
}

int main() {
	//	CITIRE 2 NUMERE DIN FISIER
	
	int a, b;

	FILE* streamFisier = NULL;
	streamFisier = fopen("Numere.txt", "r");

	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d ", &a);
		fscanf(streamFisier, "%d ", &b);
	}
	else {
		printf("Nu s-a putut deschide fisierul!\n");
	}

	printf("a=%d b=%d", a, b);

	printf("\n");

	// CITIRE VECTOR DIN FISIER - varianta 1

	int* v;
	int dim;
	
	citireVectorDinFisier1("vector1.txt", &v, &dim);
	for (int i = 0; i < dim; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	afisareVector(v, dim);
	printf("\n");

	// CITIRE VECTOR DIN FISIER - varianta 2

	int dimens = 0;
	int* vector = citireVectorDinFisier2("vector2.txt", &dimens);
	afisareVector(vector, dimens);
	printf("\n");

	// CITIRE SI AFISARE STRUCTURA DIN FISIER

	struct Telefon telefon;
	FILE* streamDateTelefon = NULL;
	streamDateTelefon = fopen("dateTelefon.txt", "r");
	
	telefon = citireDateTelefon(streamDateTelefon);
	fclose(streamDateTelefon);

	afisareTelefon(telefon);
	printf("\n");

	// CITIRE SI AFISARE VECTOR DE STRUCTURI DIN FISIER

	struct Telefon* vect;
	int dimTelefoane;

	citireVectorTelefoane1("vectorTelefoane.txt", &vect, &dimTelefoane);

	for (int i = 0; i < dimTelefoane; i++) {
		afisareTelefon(vect[i]);
		printf("\n");
	}

	// CITIRE MATRICE DE STRUCTURI DIN FISIER

	struct Telefon** matrice;
	int nrLinii;
	int* dimensiune;

	citireMatrice("matriceTelefoane.txt", &matrice, &dimensiune, &nrLinii);

	// AFISARE MATRICE DE STRUCTURI DIN FISIER

	afisareMatrice(matrice, dimensiune, nrLinii);

	// DEZALOCARE MATRICE

	dezalocareMatrice(&matrice, &dimensiune, &nrLinii);

	return 0;
}

//a = 34 b = 22
//14 25 36 67
//14 25 36 67
//1 3 6 8 2 5
//Nume = iPhone11; Memorie = 64; Pret = 2500.00
//Nume = Samsung; Memorie = 128; Pret = 4500.00
//Nume = Huawei; Memorie = 256; Pret = 3000.00
//Nume = Iphone11; Memorie = 64; Pret = 2500.00Nume = Samsung1; Memorie = 32; Pret = 1000.00
//Nume = Huawei; Memorie = 128; Pret = 1500.00
//Nume = LG2; Memorie = 16; Pret = 650.00Nume = AllView23; Memorie = 4; Pret = 500.00Nume = Chinezarie1; Memorie = 2; Pret = 600.00

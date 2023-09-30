// 1. citire valori intregi dintr-un fisier, le salveaza intr-un vector si le afiseaza

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

int* citesteVectorDinFisier(const char* numeFisier, int* nrElemente) {
	FILE* f = fopen(numeFisier, "r");
	int* vector = NULL;

	if (f != NULL) {
		fscanf(f, "%d", nrElemente);
	}

	if (*nrElemente > 0) {
		vector = (int*)malloc(sizeof(int) * (*nrElemente));
		int index = 0;
		while (!feof(f)) {
			fscanf(f, "%d", &vector[index]);
			index = index + 1;
		}
	}

	fclose(f);
	return vector;
}

void afisare(int* vector, int nrElemente) {
	int i = 0; 
	printf("Elementele vectorului sunt: ");
	for (i = 0; i < nrElemente; i++) {
		printf("%d, ", vector[i]);
	}
	printf("\n");
}

int main() {
	int nrElemente = 0;
	int* vector = citesteVectorDinFisier("vectorSimplu.txt", &nrElemente);
	afisare(vector, nrElemente);
	free(vector);
	return 0;
}

// Output: 
// Elementele vectorului sunt: 1, 3, 6, 8, 2, 5,

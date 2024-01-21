//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<malloc.h>
//
//void interschimb1(int m, int n) {
//	int aux = m;
//	m = n;
//	n = aux;
//}
//
//void interschimb2(int* a, int* b) {
//	int aux = *a;
//	*a = *b;
//	*b = aux;
//}
//
//void interschimb3(int& a, int& b) {
//	int aux = a;
//	a = b;
//	b = aux;
//}
//
//int main() {
//
//	/*char x[10];
//	for (int i = 0; i < 9; i++) {
//		x[i] = 'h';
//	}
//	x[9] = '\0';
//	printf("%s \n", x);
//
//	char* y;
//	y = (char*)malloc(sizeof(char) * 10);
//	for (int i = 0; i < 9; i++) {
//		y[i] = 97 + i;
//	}
//	y[9] = '\0';
//	printf("%s \n", y);*/
//
//	int a = 7, b = 5;
//	interschimb1(a, b);
//	printf("a=%d, b=%d\n", a, b);
//
//	interschimb2(&a, &b);
//	printf("a=%d, b=%d\n", a, b);
//
//	interschimb3(a, b);
//	printf("a=%d, b=%d\n", a, b);
//
//
//	return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

#include<stdlib.h>
#include<string.h>

void citireVector(int** v, int* dim) {
	printf("Precizati dimensiunea vectorului: \n");
	scanf("%d", dim);

	(*v) = (int*)malloc(sizeof(int) * (*dim));

	printf("Introduceti elementele vectorului: ");
	for (int i = 0; i < (*dim); i++) {
		printf("v[%d] = ", i);
		scanf("%d", &(*v)[i]);
	}
}

void afisareVector(int* v, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\nv[%d] = %d", i, v[i]);
	}
}

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

int main() {
	int* v;
	int dim;

	citireVector(&v, &dim);
	afisareVector(v, dim);

	int nrElemente = 0;
	int* vector = citesteVectorDinFisier("vectorSimplu.txt", &nrElemente);
	afisareVector(vector, nrElemente);
	free(vector);

	return 0;
}

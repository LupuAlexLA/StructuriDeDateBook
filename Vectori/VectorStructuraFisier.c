// 2. Citire carti dintr-un fisier, le salveaza intr-un vector si apoi sunt realizate diferite operatii asupra acestor elemente din vector

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
};

struct Carte citesteCarte(FILE* f) {
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

void afiseazaCarte(struct Carte carte) {
	printf("Cartea %s are %d capitole:\n", carte.titluCarte, carte.numarCapitole);
	for (int i = 0; i < carte.numarCapitole; i++) {
		printf("%s; ", carte.titluriCapitole[i]);
	}
	printf("\nAceasta are %d pagini si costa %5.2f RON.\n", carte.numarPagini, carte.pretCarte);
}

struct Carte* citesteVectorCartiDinFisier(const char* numeFisier, int* nrCarti) {
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

void afiseazaVectorCarti(struct Carte* vector, int nrCarti) {
	for (int i = 0; i < nrCarti; i++) {
		afiseazaCarte(vector[i]);
		printf("\n");
	}
}

void stergereMemorie(struct Carte** vector, int nrCarti) {
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

struct Carte cautaCarteDupaTitlu(struct Carte* vector, int nrCarti, const char* titluCautat) {
	for (int i = 0; i < nrCarti; i++) {
		if (strcmp(vector[i].titluCarte, titluCautat) == 0) {
			return vector[i];
		}
	}
}

struct Carte* cautaCartileCuPretulSubUnPrag(struct Carte* carti, int nrCarti, float pretPrag, int* nrCartiIeftine) {
	*nrCartiIeftine = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].pretCarte <= pretPrag) {
			(*nrCartiIeftine)++;
		}
	}

	struct Carte* vector = (struct Carte*)malloc(sizeof(struct Carte) * (*nrCartiIeftine));
	int index = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].pretCarte <= pretPrag) {
			// shallow copy
			vector[index] = carti[i];
			// deep copy pentru pointero
			vector[index].titluCarte = (char*)malloc(sizeof(char) * (strlen(carti[i].titluCarte) + 1));
			strcpy(vector[index].titluCarte, carti[i].titluCarte);

			vector[index].titluriCapitole = (char**)malloc(sizeof(char*) * carti[i].numarCapitole);
			for (int j = 0; j < vector[index].numarCapitole; j++) {
				vector[index].titluriCapitole[j] = (char*)malloc(sizeof(char) * (strlen(carti[i].titluriCapitole[j]) + 1));
				strcpy(vector[index].titluriCapitole[j], carti[i].titluriCapitole[j]);
			}
			index++;
		}
	}
	return vector;
}

struct Carte* cautaCartileCuPretulInInterval(struct Carte* carti, int nrCarti, float pragInferior, float pragSuperior, int* nrCartiInterval) {
	*nrCartiInterval = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].pretCarte >= pragInferior && carti[i].pretCarte <= pragSuperior) {
			(*nrCartiInterval)++;
		}
	}

	struct Carte* vector = (struct Carte*)malloc(sizeof(struct Carte) * (*nrCartiInterval));
	int index = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].pretCarte >= pragInferior && carti[i].pretCarte <= pragSuperior) {
			// shallow copy
			vector[index] = carti[i];
			// deep copy pentru pointeri
			vector[index].titluCarte = (char*)malloc(sizeof(char) * (strlen(carti[i].titluCarte) + 1));
			strcpy(vector[index].titluCarte, carti[i].titluCarte);

			vector[index].titluriCapitole = (char**)malloc(sizeof(char*) * carti[i].numarCapitole);
			for (int j = 0; j < vector[index].numarCapitole; j++) {
				vector[index].titluriCapitole[j] = (char*)malloc(sizeof(char) * (strlen(carti[i].titluriCapitole[j]) + 1));
				strcpy(vector[index].titluriCapitole[j], carti[i].titluriCapitole[j]);
			}
			index++;
		}
	}
	return vector;
}

float calculeazaPretulTotal(struct Carte* carti, int nrCarti) {
	float pretTotal = 0;
	for (int i = 0; i < nrCarti; i++) {
		pretTotal += carti[i].pretCarte;
	}
	return pretTotal;
}

float calculeazaNumarulMediuDePagini(struct Carte* carti, int nrCarti) {
	float nrMediuPagini = 0;
	if (nrCarti > 0) {
		float nrPagini = 0;
		for (int i = 0; i < nrCarti; i++) {
			nrPagini += carti[i].numarPagini;
		}
		nrMediuPagini = nrPagini / nrCarti;
	}
	return nrMediuPagini;
}

void stergereCarteDupaTitlu(struct Carte** carti, int* nrCarti, const char* titluCautat) {
	int existaCarte = 0;
	for (int i = 0; i < *nrCarti; i++) {
		if (strcmp((*carti)[i].titluCarte, titluCautat) == 0) {
			existaCarte = 1;
		}
	}

	if (existaCarte) {
		struct Carte* vector = (struct Carte*)malloc(sizeof(struct Carte) * ((*nrCarti) - 1));
		int index = 0;
		for (int i = 0; i < *nrCarti; i++) {
			if (strcmp((*carti)[i].titluCarte, titluCautat) != 0) {
				vector[index] = (*carti)[i];
				index++;
			}
			else {
				free((*carti)[i].titluCarte);
				for (int j = 0; j < (*carti)[i].numarCapitole; j++) {
					free((*carti)[i].titluriCapitole[j]);
				}
				free((*carti)[i].titluriCapitole);
			}
		}
		free(*carti);
		*carti = vector;
		(*nrCarti) -= 1;
	}
}

int main() {
	int nrCarti = 0;
	struct Carte* carti = citesteVectorCartiDinFisier("carti.txt", &nrCarti);
	printf("\nToate cartile:\n");
	afiseazaVectorCarti(carti, nrCarti);

	printf("\nCautare carte dupa titlu:\n");
	struct Carte carteaCautata = cautaCarteDupaTitlu(carti, nrCarti, "Morometii");
	afiseazaCarte(carteaCautata);

	printf("\nAfisarea cartilor cu pretul sub un prag:\n");
	int nrCartiIeftine = 0;
	struct Carte* cartileIeftine = cautaCartileCuPretulSubUnPrag(carti, nrCarti, 40, &nrCartiIeftine);
	afiseazaVectorCarti(cartileIeftine, nrCartiIeftine);
	stergereMemorie(&cartileIeftine, nrCartiIeftine);

	printf("\nAfisarea cartilor cu pretul intr-un interval:\n");
	int nrCartiInterval = 0;
	struct Carte* cartiInterval = cautaCartileCuPretulInInterval(carti, nrCarti, 40, 60, &nrCartiInterval);
	afiseazaVectorCarti(cartiInterval, nrCartiInterval);
	stergereMemorie(&cartiInterval, nrCartiInterval);

	float pretTotal = calculeazaPretulTotal(carti, nrCarti);
	printf("Pretul total al cartilor: %5.2f\n", pretTotal);
	float nrMediuPagini = calculeazaNumarulMediuDePagini(carti, nrCarti);
	printf("Numarul mediu de pagini este: %5.2f\n", nrMediuPagini);

	printf("\nStergerea unei carti din vector dupa titlu:\n");
	printf("Inainte de stergere:\n");
	afiseazaVectorCarti(carti, nrCarti);
	stergereCarteDupaTitlu(&carti, &nrCarti, "Ion");

	printf("Dupa stergere:\n");
	afiseazaVectorCarti(carti, nrCarti);

	stergereMemorie(&carti, nrCarti);
}

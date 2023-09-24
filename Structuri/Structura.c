#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define LINESIZE 256
#define DIM 5

typedef struct adresa
{
	char* strada;
	unsigned short int numar;
	char* cladire;
}Adresa;

typedef struct factura
{
	char* id_factura;
	char* id_client;
	float valoare;
	struct adresa adresa_client;
}Factura;

double valoare_facturi(Factura*, unsigned char);
double valoare_pfacturi(Factura**, unsigned char);

double valoare_facturi(Factura* vfacturi, unsigned char size) {
	double val = 0;
	for (unsigned char i = 0; i < size; i++) {
		val += vfacturi[i].valoare;
	}
	return val;
}

double valoare_pfacturi(Factura** pvfacturi, unsigned char size) {
	double val = 0;
	for (unsigned char i = 0; i < size; i++) {
		val += pvfacturi[i]->valoare;
	}
	return val;
}

int main() {
	struct factura fact_1;
	Factura* pfact_2;

	FILE* f;
	// fisierul Facturi.txt contine o factura pe fiecare linie;
	f = fopen("Facturi.txt", "r");

	char* token, file_line_buf[LINESIZE], sep_list[] = ",\n";

	// incarcarea datelor pentru fact_1
	fgets(file_line_buf, sizeof(file_line_buf), f); // prelucrare continut linia #1 din fisierul Facturi.txt
	token = strtok(file_line_buf, sep_list);
	fact_1.id_factura = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fact_1.id_factura, token);

	token = strtok(NULL, sep_list);
	fact_1.id_client = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fact_1.id_client, token);

	token = strtok(NULL, sep_list);
	fact_1.valoare = (float)atof(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.strada = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fact_1.adresa_client.strada, token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.numar = atoi(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.cladire = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fact_1.adresa_client.cladire, token);

	token = strtok(NULL, sep_list);
	if (token) {
		printf("\nEroare preluare token!");
	}

	// incarcarea datelor pentru fact_2
	fgets(file_line_buf, sizeof(file_line_buf), f); // prelucrare continut linia #2 din fisierul Facturi.txt
	// alocare memorie heap pentru factura #2 gestionata prin pfact_2
	pfact_2 = (Factura*)malloc(1 * sizeof(Factura));
	token = strtok(file_line_buf, sep_list);
	pfact_2->id_factura = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(pfact_2->id_factura, token);

	token = strtok(NULL, sep_list);
	pfact_2->id_client = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(pfact_2->id_client, token);

	token = strtok(NULL, sep_list);
	pfact_2->valoare = (float)atof(token);

	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.strada = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(pfact_2->adresa_client.strada, token);

	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.numar = atoi(token);

	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.cladire = (char*)malloc((strlen(token) + 1) * sizeof(char));
	strcpy(pfact_2->adresa_client.cladire, token);

	token = strtok(NULL, sep_list);
	if (token) {
		printf("\nEroare preluare token!");
	}

	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii factura #1:\n");
	printf("ID factura: %s\n", fact_1.id_factura);
	printf("ID client: %s\n", fact_1.id_client);
	printf("Adresa client: %s %u, %s\n", fact_1.adresa_client.strada, fact_1.adresa_client.numar, fact_1.adresa_client.cladire);
	printf("Valoare: %9.2f\n", fact_1.valoare);

	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii factura #2:\n");
	printf("ID factura: %s\n", pfact_2->id_factura);
	printf("ID client: %s\n", pfact_2->id_client);
	printf("Adresa client: %s %u, %s\n", pfact_2->adresa_client.strada, pfact_2->adresa_client.numar, pfact_2->adresa_client.cladire);
	printf("Valoare: %9.2f\n", pfact_2->valoare);

	Factura v_facturi[DIM];
	struct factura** pv_facturi; // vector cu elemente de tip Factura*

	fseek(f, 0, SEEK_SET);

	// preluare primele DIM linii din Facturi.txt in vectorul de facturi v_facturi
	// Fisierul Facturi.txt trebuie sa contina cel putin DIM linii cu facturi
	for (unsigned char i = 0; i < DIM; i++) {
		fgets(file_line_buf, sizeof(file_line_buf), f);
		token = strtok(file_line_buf, sep_list);
		v_facturi[i].id_factura = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(v_facturi[i].id_factura, token);

		token = strtok(NULL, sep_list);
		v_facturi[i].id_client = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(v_facturi[i].id_client, token);

		token = strtok(NULL, sep_list);
		v_facturi[i].valoare = (float)atof(token);

		token = strtok(NULL, sep_list);
		v_facturi[i].adresa_client.strada = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(v_facturi[i].adresa_client.strada, token);

		token = strtok(NULL, sep_list);
		v_facturi[i].adresa_client.numar = atoi(token);

		token = strtok(NULL, sep_list);
		v_facturi[i].adresa_client.cladire = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(v_facturi[i].adresa_client.cladire, token);

		token = strtok(NULL, sep_list);
		if (token) {
			printf("\nEroare preluare token!");
		}
	}

	// copiere facturi din vectorul v_facturi in vectorul pv_facturi alocat in memorie heap
	pv_facturi = (struct factura**)malloc(DIM * sizeof(struct factura*));
	for (unsigned char i = 0; i < DIM; i++) {
		pv_facturi[i] = (struct factura*)malloc(1 * sizeof(struct factura*));

		pv_facturi[i]->id_factura = (char*)malloc((strlen(v_facturi[i].id_factura) + 1) * sizeof(char));
		strcpy(pv_facturi[i]->id_factura, v_facturi[i].id_factura);

		pv_facturi[i]->id_client = (char*)malloc((strlen(v_facturi[i].id_client) + 1) * sizeof(char));
		strcpy(pv_facturi[i]->id_client, v_facturi[i].id_client);

		pv_facturi[i]->valoare = v_facturi[i].valoare;

		pv_facturi[i]->adresa_client.strada = (char*)malloc((strlen(v_facturi[i].adresa_client.strada) + 1) * sizeof(char));
		strcpy(pv_facturi[i]->adresa_client.strada, v_facturi[i].adresa_client.strada);

		pv_facturi[i]->adresa_client.numar = v_facturi[i].adresa_client.numar;

		pv_facturi[i]->adresa_client.cladire = (char*)malloc((strlen(v_facturi[i].adresa_client.cladire) + 1) * sizeof(char));
		strcpy(pv_facturi[i]->adresa_client.cladire, v_facturi[i].adresa_client.cladire);
	}

	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii facturi vector alocat la compilare:\n");
	for (unsigned char i = 0; i < DIM; i++) {
		printf("Detalii factura #%u:\n", i + 1);
		printf("ID factura: %s\n", v_facturi[i].id_factura);
		printf("ID client: %s\n", v_facturi[i].id_client);
		printf("Adresa client: %s %u, %s\n", v_facturi[i].adresa_client.strada, v_facturi[i].adresa_client.numar, v_facturi[i].adresa_client.cladire);
		printf("Valoare: %9.2f\n", v_facturi[i].valoare);
		printf("--------------------------------------------------------------\n");
	}

	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii facturi vector alocat la run-time:\n");
	for (unsigned char i = 0; i < DIM; i++) {
		printf("Detalii factura #%u:\n", i + 1);
		printf("ID factura: %s\n", pv_facturi[i]->id_factura);
		printf("ID client: %s\n", pv_facturi[i]->id_client);
		printf("Adresa client: %s %u, %s\n", pv_facturi[i]->adresa_client.strada, pv_facturi[i]->adresa_client.numar, pv_facturi[i]->adresa_client.cladire);
		printf("Valoare: %9.2f\n", pv_facturi[i]->valoare);
		printf("--------------------------------------------------------------\n");
	}

	// prelucrarea datelor dintr-un vector de facturi
	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Valoare totala facturi vector alocat la compilare: %lf\n", valoare_facturi(v_facturi, DIM));
	printf("Valoare totala facturi vector alocat la run-time: %lf\n", valoare_pfacturi(pv_facturi, DIM));

	// dezalocare zone de memorie heap utilizate
	// fact_1
	free(fact_1.id_client);
	free(fact_1.id_factura);
	free(fact_1.adresa_client.strada);
	free(fact_1.adresa_client.cladire);

	// fact_2
	free(pfact_2->id_client);
	free(pfact_2->id_factura);
	free(pfact_2->adresa_client.strada);
	free(pfact_2->adresa_client.cladire);

	// v_facturi
	for (unsigned char i = 0; i < DIM; i++) {
		free(v_facturi[i].id_client);
		free(v_facturi[i].id_factura);
		free(v_facturi[i].adresa_client.strada);
		free(v_facturi[i].adresa_client.cladire);
	}

	// pv_facturi
	for (unsigned char i = 0; i < DIM; i++) {
		free(pv_facturi[i]->id_client);
		free(pv_facturi[i]->id_factura);
		free(pv_facturi[i]->adresa_client.strada);
		free(pv_facturi[i]->adresa_client.cladire);
		free(pv_facturi[i]);
	}
	free(pv_facturi); // dezalocare vector

	fclose(f);
	return 0;

}

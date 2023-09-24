#include<stdio.h>
#include<string.h>

union union_post
{
	unsigned int id_post;	// id
	char den_post[30];		// denumire
	float salariu;			// salariu
};

struct struct_post
{
	unsigned int id_post;	// id
	char den_post[30];		// denumire
	float salariu;			// salariu
};

void main() {
	printf("Dimensiune structura definita cu union = %u\n", sizeof(union union_post));
	printf("Dimensiune structura definita cu struct = %u\n", sizeof(struct struct_post));
	
	union union_post upost;
	struct struct_post ppost;
	char uflag;

	printf("Tip de date considerat pentru uniune (I (id_post), D (den_post), S (salariu)): ");
	scanf("%c", &uflag);

	// initializare variabila uniune conform tip de date specificat la run-time (de la tastatura)
	// un singur camp este semnificativ la un moment dat din punct de vedere continut
	switch(uflag)
	{
		case 'I':
			upost.id_post = 0x12345678;
			break;
		case 'D':
			strcpy(upost.den_post, "Analist");
			break;
		case 'S':
			upost.salariu = 5000.;
			break;
		default:
			printf("Optiune introdusa gresit!");
	}

	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii post stocat in structura de tip uniune:\n");
	// snapshot structura uniune cu toate campurile
	printf("Id = 0x%p, Denumire = %s, Salariu = %.2f\n", (void*)upost.id_post, upost.den_post, upost.salariu);

	printf("\nDetalii post stocat in structura de tip uniune (modificare un singur camp la un moment dat):\n");
	// fiecare camp este accesat/afisat dupa modificarea sa
	upost.id_post = 0x12345679;
	printf("Id = 0x%p, ", (void*)upost.id_post); // continut considerat ca pointer pentru afisare cu descriptorul %p; nu este afectat continutul lui id_post

	strcpy(upost.den_post, "Zugrav");
	printf("Denumire = %s, ", upost.den_post);
	upost.salariu = 3500.;
	printf("Salariu = %.2f\n", upost.salariu);

	// initializare variabila struct cu valori pentru toate campurile
	ppost.id_post = 0x123456AA;
	strcpy(ppost.den_post, "Contabil");
	ppost.salariu = 6000.;
	printf("///////////////////////////////////////////////////////////////////////////////////\n");
	printf("Detalii post stocat in structura de tip articol (struct):\n");
	// snapshot struct cu toate campurile
	printf("Id = 0x%p, Denumire = %s, Salariu = %.2f", (void*)ppost.id_post, ppost.den_post, ppost.salariu);

	printf("\nDetalii post stocat in structura de tip uniune (modificare toate campurile la un moment dat):\n");
	ppost.id_post = ppost.id_post + 1; // id_post este persistent intre doua utilizari; continut nou = 0x123456AB
	strcpy(ppost.den_post, "Pompier");
	ppost.salariu = 8000.;
	// snapshot struct cu toate campurile dupa modificare
	printf("Id = 0x%p, Denumire = %s, Salariu = %.2f\n", (void*)ppost.id_post, ppost.den_post, ppost.salariu);
}

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define VECTOR_SIZE 10

int main() {
	unsigned char x = 103; // variabila de tip de date primar (standard); zona de memorie cu lungimea de 1 byte;
	unsigned char* px = NULL; // variabila de tip pointer; se aloca la compilare (stack segment); se aloca sizeof(px) bytes = 4 bytes : px este FAR seg:off

	// utilizare adresa variabila tip de date primar
	px = &x; // adresa de stack seg a lui x scrisa in variabila px;

	printf("///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi initiale ale variabilelor x si px:\n");
	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Continut existent la adresa din variabila px = %u\n", *px);
	printf("Adresa segment stack unde variabila x a fost alocata la compilare = 0x%p\n", &x);
	printf("Continut (valoare intreaga) variabila x = %u\n", x);

	*px = x + 3; // modificare indirecta a variabilei x
	printf("Adrese si continuturi ale variabilelor x si px dupa modificarea continutului lui x:\n");
	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment stack continuta de variabila px = 0x%p\n", px);
	printf("Continut existent la adresa din variabila px = %u\n", *px);
	printf("Adresa segment stack unde variabila x a fost alocata la compilare = 0x%p\n", &x);
	printf("Continut (valoare intreaga) variabila x = %u\n", x);

	// pointer constant la int
	int vint = 13, j = 9; 
	int* const pci = &vint; // obligatoriu, initializarea pci la momentul declararii

	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si pci:\n");
	printf("Adresa segment stack unde variabila pointer constant pci a fost alocata la compilare = 0x%p\n", &pci);
	printf("Adresa segment stack continuta de variabilla pointer constant pci = 0x%p\n", pci);
	printf("Continut existent la adresa din variabila pointer constant pci = %u\n", *pci);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint = %d\n", vint);
	// pci = &j; // tentativa de modificare pointer constant la int (eroare de compilare!)

	// pointer la int constant
	int const* pint;
	pint = &vint;

	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si pint:\n");
	printf("Adresa segment stack unde variabila pointer la int constant pint a fost alocata la compilare = 0x%p\n", &pint);
	printf("Adresa segment stack continuta de variabilla pointer la int constant pint = 0x%p\n", pint);
	printf("Continut existent la adresa din variabila pointer la int constant pint = %u\n", *pint);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint = %d\n", vint);
	// *pint = vint + 5; // tentativa de modificare pointer la int constant (eroare de compilare!)

	// pointer constant la int constant
	const int* const pint2 = &vint;
	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si pint2:\n");
	printf("Adresa segment stack unde variabila pointer constant la int constant pint2 a fost alocata la compilare = 0x%p\n", &pint2);
	printf("Adresa segment stack continuta de variabilla pointer constant la int constant pint2 = 0x%p\n", pint2);
	printf("Continut existent la adresa din variabila pointer constant2 la int constant pint = %u\n", *pint2);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint = %d\n", vint);
	// pint2 = &j; // tentativa de modificare pointer constant la int (eroare de compilare!)
	// *pint = vint + 5; // tentativa de modificare pointer la int constant (eroare de compilare!)

	// utilizare adresa variabila tip vector
	unsigned char vx[VECTOR_SIZE]; // variabila de tip vector; VECTOR_SIZE elemente alocate, fiecare avand lungimea de 1 byte
	px = vx; // scriere adresa de segment stack a lui vx in px
	for (unsigned char i = 0; i < sizeof(vx); i++) {
		px[i] = x + i; // px[i] <=> *(px + i)
	}

	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi ale variabilelor vx si px dupa initializarea elementelor din vx:\n");
	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment stack continuta de variabilla px = 0x%p\n", px);
	printf("Adresa segment stack unde variabila vx a fost alocata la compilare = 0x%p\n", &vx);

	for (unsigned char i = 0; i < sizeof(vx); i++) {
		printf("Element vx[%u]: Adresa segment stack = 0x%p, Continut (valoare intreaga) = %u\n", i + 1, px + i, px[i]);
	}

	// utilizare string-uri
	char str[] = "Aplicatie in C"; // byte-ul 0 pus implicit ca terminator de sir de caractere; rol de flag pentru functiile care prelucreaza siruri de caractere
	unsigned char* ppc = (unsigned char*)str;
	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi ale variabilelor str si ppc dupa initializarea elementelor din str:\n");
	printf("Adresa segment stack unde variabila ppc a fost alocata la compilare = 0x%p\n", &ppc);
	printf("Adresa segment stack continuta de variabilla ppc = 0x%p\n", ppc);
	printf("Adresa segment stack unde variabila str a fost alocata la compilare = 0x%p\n", &str);
	printf("Dimensiune vector = %u elemente, Lungime sir de caractere = %d caractere/simboluri, continut (string ASCII) variabila str/ppc = %s\n", sizeof(str), strlen(str), str);

	printf("Continut (format hexa) la nivele elemente vector str/ppc\n");
	for (unsigned char i = 0; i < sizeof(str); i++) {
		printf("Element str[%u]: 0x%02X\n", i + 1, ppc[i]);
	}

	str[strlen(str)] = 1; // rescrierea terminatorului de sir de caractere (byte cu valoarea 0)
	printf("Adrese si continuturi ale variabilelor str si ppc dupa rescrierea terminatorului sir de caractere din str:\n");
	printf("Adresa segment stack unde variabila ppc a fost alocata la compilare = 0x%p\n", &ppc);
	printf("Adresa segment stack continuta de variabilla ppc = 0x%p\n", ppc);
	printf("Adresa segment stack unde variabila str a fost alocata la compilare = 0x%p\n", &str);
	printf("Dimensiune vector = %u elemente, Lungime sir de caractere = %d caractere/simboluri, continut (string ASCII) variabila str/ppc = %s\n", sizeof(str), strlen(str), str);
	printf("Continut (format hexa) la nivele elemente vector str/ppc\n");
	for (unsigned char i = 0; i < sizeof(str); i++) {
		printf("Element str[%u]: 0x%02X\n", i + 1, ppc[i]);
	}

	// utilizare vectori de pointeri
	int* vpi[VECTOR_SIZE];
	for (unsigned char i = 0; i < VECTOR_SIZE; i++) {
		vpi[i] = &vint;
	}
	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi ale variabilelor vint si vpi dupa initializarea elementelor din vpi:\n");
	printf("Adresa segment stack unde variabila vector vpi a fost alocata la compilare = 0x%p\n", &vpi);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);

	for (unsigned char i = 0; i < VECTOR_SIZE; i++) {
		printf("Element vpi[%u]: Adresa segment stack = 0x%p, Continut (adresa segment stack variabila vint) = 0x%p\n", i + 1, vpi + i, vpi[i]);
	}

	vpi[1] = vpi[0] + 1; // aritmetica de pointeri aplicata pentru int (&vint + 1)
	printf("Adrese si continuturi ale variabilelor vint si vpi dupa modificarea elementului vpi[1]:\n");
	printf("Adresa segment stack unde variabila vector vpi a fost alocata la compilare = 0x%p\n", &vpi);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);

	for (unsigned char i = 0; i < VECTOR_SIZE; i++) {
		printf("Element vpi[%u]: Adresa segment stack = 0x%p, Continut (adresa segment stack variabila vint) = 0x%p\n", i + 1, vpi + i, vpi[i]);
	}

	// alocarea vector la run-time
	unsigned char n = (unsigned char)(strlen(str) - 2); // lungime determinata de existenta unui byte cu valoarea 0
	px = (unsigned char*)malloc(n * sizeof(unsigned char));

	for (char i = 0; i < n; i++) {
		px[i] = ppc[i] + i;
	}

	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi ale variabilelor px si n dupa alocare si initializare memorie heap:\n");
	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment heap continuta de variabilla px = 0x%p\n", px);
	printf("Continut n (dimensiune vector) = %u elemente\n", n);

	for (char i = 0; i < n; i++) {
		printf("Element px[%u]: %u\n", i + 1, px[i]);
	}

	// dezalocare memorie heap
	free(px);

	// mapare pointer peste o variabila existenta la nivel de byte

	int z = 0x7511DD80;
	unsigned char* pz = NULL;

	pz = (unsigned char*)&z;

	printf("\n///////////////////////////////////////////////////////////////////////////\n\n");
	printf("Adrese si continuturi initiale ale variabilelor z si pz:\n");
	printf("Adresa segment stack unde variabila pz a fost alocata la compilare = 0x%p\n", &pz);
	printf("Adresa segment stack continuta de variabilla pz = 0x%p\n", pz);
	printf("Adresa segment stack unde variabila z a fost alocata la compilare = 0x%p\n", &z);
	printf("Continut (valoare intreaga) variabila z = %d\n", z);

	// parsare byte cu byte a grupului (int = 4 bytes) alocat pentru variabila z la nivel fizic (reprezentare BIG ENDIAN)
	printf("Continut (format hexa BIG ENDIAN) variabila z = 0x\n");
	for (char i = 0; i < sizeof(int); i++) {
		printf("%02X", pz[i]);
	}
	printf("\n");

	// parsare byte cu byte a grupului (int = 4 bytes) alocat pentru variabila z la nivel logic (reprezentare LITTLE ENDIAN)
	printf("Continut (format hexa LITTLE ENDIAN) variabila z = 0x\n");
	for (char i = sizeof(int) - 1; i >= 0; i--) {
		printf("%02X", pz[i]);
	}
	printf("\n");

	pz[2] = 0x89; // modificare byte cu offset 2 la nivel fizic (continutul anterior este 0x11, byte-ul 2 din initializarea lui z)
	// deoarece stocarea datelor la nivel fizic este conform LITTLE ENDIAN

	printf("Adrese si continuturi dupa modificare ale variabilelor z si pz:\n");
	printf("Adresa segment stack unde variabila pz a fost alocata la compilare = 0x%p\n", &pz);
	printf("Adresa segment stack continuta de variabilla pz = 0x%p\n", pz);
	printf("Adresa segment stack unde variabila z a fost alocata la compilare = 0x%p\n", &z);
	printf("Continut (valoare intreaga) variabila z = %d\n", z);
	printf("Continut (format hexa BIG ENDIAN) variabila z = 0x\n");

	printf("Continut (format hexa BIG ENDIAN) variabila z = 0x\n");
	for (char i = 0; i < sizeof(int); i++) {
		printf("%02X", pz[i]);
	}
	printf("\n");

	printf("Continut (format hexa LITTLE ENDIAN) variabila z = 0x\n");
	for (char i = sizeof(int) - 1; i >= 0; i--) {
		printf("%02X", pz[i]);
	}
	printf("\n");

	return 0;
}

#include<stdio.h>

double f(float x, float y) {
	double s;
	s = x + y;
	return s;
}

double g(float x, float y) {
	double d;
	d = x / y;
	return d;
}

double FP(float x, float y, double(*fp)(float, float)) {
	x = x + 1;
	y = (float)(y + 2.2);
	double op = fp(x, y);
	return op;
}

int main() {
	float a = 1.2f;
	float b = 4.7f;
	double c;

	// definire si utilizare pointer la functie
	double (*pFct)(float, float); // var locala functiei main(); alocare la compilare in stack segment

	pFct = f; // "incarcare" adresa inceput functie sumaValoare in pSumaVal

	printf("////////////////////////////////////////////////////////////////////////////////////////\n");
	printf("Adresa si continut initial variabila pointer la functie pFct:\n");
	printf("Adresa segment stack unde variabila pFct a fost alocata la compilare = 0x%p\n", &pFct);
	printf("Adresa segment de cod continuta de variabila pFct= 0x%p\n", pFct);

	c = pFct((float)(a + 1), (float)(b + 2.2));
	printf("Rezultat apel functie f prin pointer la functie: %lf\n", c);

	c = FP(a, b, pFct);
	printf("\nRezultat #1 apel functie cu parametru pointer la functie: %lf\n", c);

	pFct = g; // "incarcare" adresa inceput functie sumaValoare in pSumaVal

	printf("\n////////////////////////////////////////////////////////////////////////////////////////\n");
	printf("Adresa si continut dupa modificare pentru variabila pointer la functie pFct:\n");
	printf("Adresa segment stack unde variabila pFct a fost alocata la compilare = 0x%p\n", &pFct);
	printf("Adresa segment de cod continuta de variabila pFct= 0x%p\n", pFct);

	c = pFct((float)(a + 1), (float)(b + 2.2));
	printf("Rezultat apel functie g prin pointer la functie: %lf\n", c);

	c = FP(a, b, pFct);
	printf("\nRezultat #2 apel functie cu parametru pointer la functie: %lf\n", c);

	return 0;
}

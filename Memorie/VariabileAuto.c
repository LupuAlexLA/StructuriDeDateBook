#include<stdio.h>

int main() {
	// Definire si utilizare variabile automatice
	int a = 8;
	auto b = 9.682;
	auto double c;
	c = 9.682;

	double x = a + b;
	printf("a + b = %lf\n", x);
	x = a + c;
	printf("a + c = %lf\n", x);

	auto ps = "string_1";
	auto int psi = "string_2";
	auto char* psc = "string_3";

	printf("ps = %s\n", ps);
	printf("psi = %s\n", psi);
	printf("psc = %s\n", psc);

	ps = psc;
	printf("\nps = %s\n", ps);

	a = psi;
	printf("a = %s\n", a);

	return 0;
}

//Output:
//a + b = 17.000000
//a + c = 17.682000
//ps = string_1
//psi = string_2
//psc = string_3
//
//ps = string_3
//a = string_2

#include<stdio.h>

int f() {
	static int x = 0;
	x++;
	return x;
}

int main() {
	// Definire si utilizare variabile statice
	int j;
	for (j = 0; j < 10; j++) {
		printf("Rezultat apel functie f: %d\n", f());
	}

	return 0;
}

//Output:

//Rezultat apel functie f : 1
//Rezultat apel functie f : 2
//Rezultat apel functie f : 3
//Rezultat apel functie f : 4
//Rezultat apel functie f : 5
//Rezultat apel functie f : 6
//Rezultat apel functie f : 7
//Rezultat apel functie f : 8
//Rezultat apel functie f : 9
//Rezultat apel functie f : 10

#include<stdio.h>

int j = 2;

extern void h();

void g() {
	h();
	printf("j = %d\n", j);
}

int main() {
	j = 5;
	g();

	return 0;
}

//exista un fisier flmpl2.c
//Output: 
//j = 6

#include<stdio.h>
#include"headers.h"

int i;

int main() {
	i = 3;

	f();
	printf("i = %d\n", i);

	return 0;
}

//exista un fisier flmpl.c
//Output:
//i = 4

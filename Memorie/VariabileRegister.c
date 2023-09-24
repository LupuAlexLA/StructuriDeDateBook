#include<stdio.h>

int main() {
	// Definire si utilizarea variabile register
	register int vreg;
	int d;

	d = 0x18; // d = 24 in baza 10
	vreg = d;

	printf("vreg = 0x%08x (%d)\n", vreg, vreg);

	_asm // introduce secventa scrisa in cod limbaj de asamblare
	{
		mov eax, vreg; // incarca registrul EAX cu continutul variabilei vreg
		mov vreg, ecx; // rescrie variabila vreg cu continutul arbitrar al registrului ECX
	};

	printf("vreg = 0x%08X\n", vreg);

	return 0;
}

//Output:
//vreg = 0x00000018 (24)
//vreg = 0x00EFFB0C

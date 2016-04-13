#include <stdio.h>

typedef unsigned char octet;

void afficher_binaire(octet c) {
	do {
    if (c & 1) putchar('1');
    else       putchar('0');
    c >>= 1; // ou c /= 2;
  } while (c);
}

void affiche(size_t s, octet a) {
	printf("%02zu : ", s);
	afficher_binaire(a);
	printf("  %d ", (unsigned int) a);
	if (a > 32 && a <= 126) {
		printf("%c", a);
	}
	putchar('\n');
}

void dump_mem(octet* a, size_t N) {
	printf("A partir de %p : \n", a);
	for (int i = 0; i < N; ++i) {
		affiche(i, a[i]);
	}
}

int main(void) {
	int test1 = 80;
	double test2 = 0.5;
	double test3 = 0.1;
	
	dump_mem( (octet*) &test1, sizeof(test1) );
	dump_mem( (octet*) &test2, sizeof(test2) );
	dump_mem( (octet*) &test3, sizeof(test3) );
 
  return 0;
}

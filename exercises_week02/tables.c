#include <stdio.h>

int main(void) {
	printf("Tables de multiplication \n \n");
	for (int i = 0; i <= 10 ; ++i) {
		printf("Table de %d : \n", i);
		for (int j = 1; j <= 10; ++j) {
			printf("%d * %d = %d \n", i, j, i*j);
		}
	}
}

#include <stdio.h>


void swap(int* a, int* b);


void swap (int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{
    int i = 10;
    int j = 55;

    printf("Avant : i=%d et j=%d\n", i, j);
    swap(&i, &j);
    printf("Après : i=%d et j=%d\n", i, j);
    return 0;
}

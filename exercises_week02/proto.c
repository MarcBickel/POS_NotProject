#include <stdio.h>

int demander_nombre(void);



int main(void) {
	int number = demander_nombre();
	printf("This is your number : %d", number);
}

int demander_nombre(void) {
	int a;
 
	printf("Enter an integer\n");
	scanf("%d", &a);
 
	return a;
}

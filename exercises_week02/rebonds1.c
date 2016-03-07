#include <math.h>
#include <stdio.h>



int main(void) {
	double const g = 9.81;
	double h0 = 0;
	double eps = 0;
	int nbr = 0;
	double v = 0;
	double v1 = 0;
	double h1 = 0;
	
	printf("Veuillez rentrer la hauteur initiale ( >= 0) : ");
	scanf("%lf", &h0);
	
	printf("Veuillez rentrer le coefficient de rebond ( 0 <= eps > 1) : ");
	scanf("%lf", &eps);
	
	printf("Veuillez rentrer le nombre de rebonds : ");
	scanf("%d", &nbr);
	
	
	h1 = h0;
	for (int i = 0; i < nbr; ++i) {
		v = sqrt(2*h1*g);
		v1 = v * eps;
		h1 = (v1 * v1) / (2 * g);
	}
	
	printf("Au %d ème rebond, la hauteur sera de %lf m", nbr, h1);
}

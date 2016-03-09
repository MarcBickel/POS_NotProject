#include <stdio.h>


double scalaire(const double u[], const double v[], size_t taille);

double scalaire(const double u[], const double v[], size_t taille) {
	double result = 0;
	for (int i = 0; i < taille; ++i) {
		result += u[i] * v[i];
	}
	return result;
}

int main(void) {
	int const N_MAX = 10;
	double v1[N_MAX];
	double v2[N_MAX];
	size_t n = 0;
	
	do {
		printf("Veuillez rentrer la taille effective des vecteurs : ");
		scanf("%d", &n);
	} while (n < 1 || n > N_MAX);
	
	for (int i = 0; i < n; ++i) {
		
		printf("Entrez maintenant la valeur %d du vecteur v1 : ", i + 1);
		scanf("%lf", &v1[i]);
	}
	
	for (int i = 0; i < n; ++i) {
		
		printf("Entrez maintenant la valeur %d du vecteur v2 : ", i + 1);
		scanf("%lf", &v2[i]);
	}
	
	
	double result = scalaire(v1, v2, n);
	printf("Voici le resultat du produit scalaire des deux vecteurs que vous avez rentrés : %lf", result);
	
	return 0;
}

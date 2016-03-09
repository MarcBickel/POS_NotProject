#include <stdio.h>

#define N 10

typedef struct Matrices_struct {
	int lignes;
	int colonnes;
	double valeurs[N][N];
} Matrice;

Matrice lire_matrice(void);
Matrice multiplication(const Matrice a, const Matrice b);
void affiche_matrice(const Matrice m);

Matrice lire_matrice(void) {
	int lignes = 0;
	int colonnes = 0;
	printf("Saisie d'une matrice \n");
	printf("Nombre de lignes : ");
	scanf("%d", &lignes);
	printf("Nombre de colonnes : ");
	scanf("%d", &colonnes);
	
	double mat[lignes][colonnes];
	
	for (int i = 0; i < lignes; ++i) {
		for (int j = 0; j < colonnes; ++j) {
			printf("M[%d, %d] = ", i, j);
			scanf("%lf", &mat[i][j]);
		}
	}
	
	struct Matrice result = {int lignes, int colonnes, double mat[lignes][colonnes]};
	return result;
}

Matrice multiplication(const Matrice a, const Matrice b) {
	
}

void affiche_matrice(const Matrice m) {
	for (int i = 0; i < m.lignes; ++i) {
		for (int j = 0, j < m.colonnes; ++j) {
			printf("M[%d, %d] = %lf", i, j, m[i][j]);
	}
}

int main(void) {
	
}

/**
 * @file muimp
 * @brief File reader/writer for 2D simplified ascii images. 
 *
 * @date 1 March 2016
 */

#include <stdio.h>
#include <string.h>

//Dimensions maximales des images
#define MAX_IMAGE_HEIGHT 100
#define MAX_IMAGE_WIDTH 100
//Nombre de demandes maximales pour les noms des fichiers
#define NB_DEMANDES 3

typedef double Pixel;

struct Image {
	Pixel content[MAX_IMAGE_HEIGHT][MAX_IMAGE_WIDTH];
	int height;
	int width;
};

//Prototypes
struct Image diamond(int height, int width, int diagonal);
void display(FILE* sortie, struct Image image);
int write_to_file(char nom_fichier[FILENAME_MAX + 1], struct Image image);
struct Image read_from_file(char nom_fichier[FILENAME_MAX + 1]);
struct Image filter(struct Image image, struct Image masque);
int modulo(int numerateur, int denominateur);
int demander_int(int lower, int upper, char name[]);


struct Image diamond(int height, int width, int diagonal) {
	//Forcer les images de taille impaire. 
	width  |= 1;
	height |= 1;
	
	struct Image image;
	image.height = height;
	image.width = width;
	//Initialisation des toutes les valeurs utilisées des pixels à 0.0.
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image.content[i][j] = 0.0;
		}
	}
	
	int centreX = (width-1) / 2;
	int centreY = (height-1) / 2;
	
	//Parcourt la moitié des lignes
	for (int numLigne = 0; numLigne <= diagonal / 2; ++numLigne) {
		int gauche = centreX - (numLigne - centreY + diagonal/2);
		int droite = centreX + (numLigne - centreY + diagonal/2);
		for (int j = gauche; j <= droite; ++j) {
			image.content[numLigne][j] = 1.0;
			//Copie sur la ligne horizontalement symétrique.
			image.content[height - 1 - numLigne][j] = 1.0;
		}
	}
	
	return image;
	
	
}

void display(FILE* sortie, struct Image image) {
	for (int i = 0; i < image.height; ++i) {
		for (int j = 0; j < image.width; ++j) {
			if (image.content[i][j] == 0.0) {
				fprintf(sortie, ". ");
			} else if (image.content[i][j] == 1.0) {
				fprintf(sortie, "+ ");
			} else {
				fprintf(sortie, "* ");
			}
			 
		}
	fprintf(sortie, "\n");
	}
	fprintf(sortie, "\n");
}

int write_to_file(char nom_fichier[FILENAME_MAX + 1], struct Image image) {
	FILE* f = NULL;
	int nb = 0;
	
	do {
		++nb;
		f = fopen(nom_fichier, "w");
    
		if (f == NULL) {
		  printf("Impossible d'ouvrir le fichier \"%s\"\n", nom_fichier);
		} else {
		  printf("Fichier %s ouvert et lu :\n", nom_fichier);
		}
  } while ((f == NULL) && (nb < NB_DEMANDES));
  
  if (f == NULL) {
	  return 1;
  } else {
	  fprintf(f, "%d\n", image.width);
	  fprintf(f, "%d\n", image.height);
	  
	  //Ecriture dans le fichier
	  display(f, image);
	  
	  //Fermeture du fichier
	  fclose(f);
	  return 0;
  }
}

struct Image read_from_file(char nom_fichier[FILENAME_MAX + 1]) {
	//Image à retourner en cas d'erreur
	struct Image error;
	error.height = 0;
	error.width = 0;
	
	if (nom_fichier[0] == '\0') {
      return error;
    }
	FILE* f = NULL;
	f = fopen(nom_fichier, "r");
	if (f == NULL) {
		return error;
	}
	struct Image result;
	fscanf(f, "%d", &result.width);
	fscanf(f, "%d", &result.height);
	//Si les dimensions sont trop grandes
	if (result.width > MAX_IMAGE_WIDTH || result.height > MAX_IMAGE_HEIGHT) {
		return error;
	}
	
	int c;
	int i = 0;
	int j = 0;
	do {
		c = fgetc(f);
		if (c != (int) '\n' && c != (int) ' ') {
			if (c == (int) '.') {
				result.content[i][j] = 0.0;
			} else if (c == (int) '+') {
				result.content[i][j] = 1.0;
			} else if (c == (int) '*') {
					result.content[i][j] = 2.0;
			}
			j++;
			if (j >= result.width) {
				j = 0;
				++i;
			}
		}
	} while (!feof(f));
	
	fclose(f);
	return result;
}

struct Image filter(struct Image image, struct Image masque) {
	struct Image result;
	result.height = image.height;
	result.width = image.width;
	int N;
	if (masque.height != masque.width) {
		printf("Le masque n'est pas carré !\n");
	} else {
		N = masque.height;
	}
	
	for (int i = 0; i < result.height; ++i) {
		for (int j = 0; j < result.width; ++j) {
			Pixel current = 0.0;
			for (int k = 0; k < N; ++k) {
				for (int l = 0; l < N; ++l) {
					current += image.content[modulo(i + N/2 - l, image.height)][modulo(j + N/2 - k, image.width)] * masque.content[k][l];
				}
			}
			result.content[i][j] = current;
		}
	}
	
	return result;
}

/* Petite fonction que me permet de pallier au fait
 * que l'operateur modulo peut retourner un nombre 
 * negatif. 
 */ 
int modulo(int numerateur, int denominateur) {
	int result = numerateur % denominateur;
	if (result >= 0) {
		return result;
	} else {
		return result + denominateur;
	}
}

/* Fonction que permet de rentrer un int (et
 * de vérifier que c'en est bien un) par la console.
 */
int demander_int(int lower, int upper, char name[]) {
	int result = lower - 1;
	int j = 0;
	do {
		printf("Veuillez rentrer la %s (entre %d et %d) : ", name, lower, upper);
		fflush(stdout);
		j = scanf("%d", &result);
		if (j != 1) {
			printf("Ce que vous avez rentré n'est pas un entier valide. Veuillez recommencer.\n");
			//Vidage du tampon
			while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	} while (!feof(stdin) && !ferror(stdin) && ((j != 1) || (result < lower) || (result > upper)));
	return result;
}
	
int main(void) {
	int height = 0;
	int width = 0;
	int diagonal = 0;
	char name[FILENAME_MAX + 1];
	size_t size = 0;
	struct Image masque;
	masque.height = 3;
	masque.width = 3;
	masque.content[0][0] = -2.0;
	masque.content[0][1] = 0.0;
	masque.content[0][2] = 2.0;
	masque.content[1][0] = -2.0;
	masque.content[1][1] = 0.0;
	masque.content[1][2] = 2.0;
	masque.content[2][0] = -2.0;
	masque.content[2][1] = 0.0;
	masque.content[2][2] = 2.0;
	
	//Affichage simple du diamond
	printf("Bonjour !\n");
	height = demander_int(0, MAX_IMAGE_HEIGHT, "hauteur");
	width = demander_int(0, MAX_IMAGE_WIDTH, "largeur");
	diagonal = demander_int(0, 50, "diagonale");
	display(stdout, diamond(height, width, diagonal));
	
	
	printf("Veuillez rentrer le nom de fichier que vous souhaitez utiliser afin de stocker l'image: ");
	//Vidage des tampons
	fflush(stdout);
	while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
	fgets(name, FILENAME_MAX + 1, stdin);
	
	//On enlève le dernier char enregistré par fgets, qui est un \n
	size = strlen(name);
	if ((size >= 1) && (name[size-1] == '\n')) {
        name[--size] = '\0';
	}
	
	//Ecriture dans le fichier
	write_to_file(name, diamond(height, width, diagonal));
	
	//Affichage depuis le fichier où l'on a écrit
	display(stdout, read_from_file(name));
	
	//Affichage du diamond filtré
	display(stdout, filter(diamond(height, width, diagonal), masque));
	
	return 0;
}

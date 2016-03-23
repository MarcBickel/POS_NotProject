#include <stdio.h>
#include <string.h>
 
/* taille maximale pour un nom */
#define TAILLE_NOM 1024 
 
int main(void)
{
  char const nom_fichier[] = "data.dat"; /* le nom du fichier */
  FILE* sortie;
  int taille_lue;
 
  char nom[TAILLE_NOM]; /* pour stocker le "nom" à lire depuis le clavier */
  unsigned int age;     /* pour stocker l'"âge" à lire depuis le clavier */
 
  /* Ouverture de data.dat en écriture (w=write) */
  sortie = fopen(nom_fichier, "w");
 
  /* on teste si l'ouverture du flot s'est bien réalisée */
  if (sortie == NULL) {
    fprintf(stderr,
            "Erreur: le fichier %s ne peut etre ouvert en écriture !\n",
            nom_fichier);
    return 1; /* retourne un autre chiffre que 0 car il y a eu une erreur */
  }
 
  /* itération sur les demandes à entrer :
     on continue tant que stdin est lisible */
  while (! feof(stdin)) {
 
    /* tant qu'un nom vide est entré */
    do {
      printf("Entrez un nom (CTRL+D pour terminer) : "); fflush(stdout);
      fgets(nom, TAILLE_NOM, stdin);
      taille_lue = strlen(nom) - 1;
      if ((taille_lue >= 0) && (nom[taille_lue] == '\n'))
        nom[taille_lue] = '\0';
    } while (!feof(stdin) && (taille_lue < 1));
 
    if (! feof(stdin)) {
      /* L'utilisateur a bien saisi un nom, on peut donc lui demander
       * de saisir l'age.
       */
      printf("âge : "); fflush(stdout);
      taille_lue = scanf("%u", &age);
 
      if (taille_lue != 1) {
        printf("Je vous demande un age (nombre entier positif) pas "
               "n'importe quoi !\nCet enregistrement est annulé.\n");
        while (getc(stdin) != '\n'); /* vide le tampon d'entrée */
      } else {
        getc(stdin); /* récupère le \n résiduel */
        /* ecriture dans le fichier */
        fprintf(sortie, "%s %d\n", nom, age);
      }
	}
  }
 
  /* purisme : retour a la ligne pour finir proprement la question */
  putchar('\n');
 
  fclose(sortie); /* fermeture du fichier */
 
  return 0;
}

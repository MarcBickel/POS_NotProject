#include <stdio.h>
#include <string.h>
 
/* ===== CONSTANTES ===== */
 
/* nombre maximum de demandes en cas d'erreur */
#define NB_DEMANDES 3
 
/* taille maximum d'une Statistique : au plus 256 car il n'y a pas plus
   que 256 char. */
#define TAILLE 256 
 
/* bornes sur les caractères à prendre en compte */
unsigned char start =  32;
unsigned char stop  = 253;
 
 
/* ===== DEFINITIONS DE TYPES ====== */
 
typedef unsigned long int Statistique[TAILLE];
 
 
/* ===== FONCTIONS ====== */
FILE* demander_fichier();
 
void initialise_statistique(Statistique a_initialiser);
/* Rappel : les tableaux sont toujours passés par référence. Pas
   besoin de pointeur supplémentaire ici */
 
unsigned long int collecte_statistique(Statistique a_remplir, 
                                       FILE* fichier_a_lire);
 
void affiche(Statistique a_afficher, unsigned long int total,
             unsigned short int taille);
 
/* ====================================================================== */
int main(void)
{
  FILE* fichier = demander_fichier();
  if (fichier == NULL) {
    printf("=> j'abandonne !\n");
    return 1;
  } else {
    Statistique stat;
    initialise_statistique(stat);
    affiche(stat, collecte_statistique(stat, fichier), stop - start + 1);
    fclose(fichier);
  }
 
  return 0;
}
 
/* ======================================================================
 * Fonction demander_fichier
 * ----------------------------------------------------------------------
 * In:   Un fichier (par référence) à ouvrir.
 * Out:  Ouvert ou non ?
 * What: Demande à l'utilisateur (au plus NB_DEMANDES fois) un nom de fichier
 *       et essaye de l'ouvrir en lecture.
 * ====================================================================== */
FILE* demander_fichier()
{
  FILE* f = NULL;
  char nom_fichier[FILENAME_MAX+1];
  size_t taille_lue = 0;
  unsigned short int nb = 0;
 
  do {
    ++nb;
 
    /* demande le nom du fichier */
    do {
      printf("Nom du fichier à lire : "); fflush(stdout);
      fgets(nom_fichier, FILENAME_MAX+1, stdin);
      taille_lue = strlen(nom_fichier);
      if ((taille_lue >= 1) && (nom_fichier[taille_lue-1] == '\n'))
        nom_fichier[--taille_lue] = '\0';
    } while ((taille_lue == 0) && !feof(stdin));
 
    if (nom_fichier[0] == '\0') {
      return NULL;
    }
 
    /* essaye d'ouvrir le fichier */
    f = fopen(nom_fichier, "r");
    
    /* est-ce que ça a marché ? */
    if (f == NULL) {
      printf("-> ERREUR, je ne peux pas lire le fichier \"%s\"\n",
             nom_fichier);
    } else {
      printf("-> OK, fichier \"%s\" ouvert pour lecture.",
             nom_fichier);
    }
  } while ((f == NULL) && (nb < NB_DEMANDES));
 
  /* la valeur de retour est le résultat du test entre (): 0 ou 1 */
  return f;
}
 
 
/* ======================================================================
 * Fonction initialiser_statistique
 * ----------------------------------------------------------------------
 * In:   Une Statistique à initialiser.
 * What: Initialiser tous les éléments d'une Statistique à zéro.
 * ====================================================================== */
void initialise_statistique(Statistique stat)
{
  int i;
  for (i = 0; i < TAILLE; ++i) {
    stat[i] = 0;
  }
}
 
/* ======================================================================
 * Fonction collecte_statistique
 * ----------------------------------------------------------------------
 * In:   Une Statistique à remplir et le fichier à lire.
 * Out:  Le nombre d'éléments comptés dans la Statistique.
 * What: Lit tous les caractères dans le fichier et compte dans la Statistique
 *       combien de fois chaque caractère apparait dans le fichier.
 * ====================================================================== */
unsigned long int collecte_statistique(Statistique stat, FILE* f)
{
  int c;                    /* le caractère lu             */
  unsigned long int nb = 0; /* le nombre d'éléments comptés */
 while ((c = getc(f)) != EOF) {
    /* est-ce que le caractère lu est dans l'intervalle qu'on étudie ? */
    if (( ((unsigned char) c) >= start) &&
        ( ((unsigned char) c) <= stop ) ) {
      ++(stat[c - start]); /* on incrément la statistique pour ce caractère */
      ++nb; /* on incrémente le nombre total d'éléments comptés */
    }
  }
 
  return nb;
}
 
/* ======================================================================
 * Fonction affiche
 * ----------------------------------------------------------------------
 * In:   La Statistique à afficher, le nombre par rapport auquel on affiche
 *       les pourcentages (si 0 recalcule ce nombre comme la somme des
 *       éléments) et la taille du tableau.
 * What: Affiche tous les éléments d'une Statistique (valeurs absolue et
 *       relative).
 * ====================================================================== */
void affiche(Statistique stat, unsigned long int nb, unsigned short int taille)
{
  unsigned short int i;
 
  if (nb == 0) { /* on doit calculer la somme si nb == 0 */
    for (i = 0; i < taille; ++i)
      nb += stat[i];
  }
 
  printf("STATISTIQUES :\n");
  for (i = 0; i < taille; ++i) {
    /* on n'affiche que les résultats pour des statistiques supérieures à 0 */
    if (stat[i] != 0) {
      printf("%c : %10lu - %6.2f%%\n", (char) (i+start), stat[i],
             100.0 * stat[i] / (double) nb);
    }
  }
}

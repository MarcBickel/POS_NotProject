#include <stdio.h>
 
int demander_nombre(int a, int b)
{
   int res;
 
   do {
       printf("Entrez un nombre entier compris entre %d et %d :",
              a, b);
       scanf("%d", &res);
    } while ((res < a) || (res > b));
    return res;
}
 
int main(void) {
  double valeur1 = 3.14159265358;
  double valeur2 = 1.42857142857;
  double valeur3 = -12.344556667;
  double* choix = NULL;    /* On initialise le pointeur sur NULLe part */
 
  switch (demander_nombre(1,3)) {
    case 1: choix = &valeur1; /* la valeur de choix est l'adresse de valeur1 */
      break;
    case 2: choix = &valeur2; /* la valeur de choix est l'adresse de valeur2 */
      break;
    case 3: choix = &valeur3; /* la valeur de choix est l'adresse de valeur3 */
      break; 
  }
 
  printf("Vous avez choisi %lf \n",
         *choix /* on affiche la valeur pointée par choix */
        );
  return 0;
}

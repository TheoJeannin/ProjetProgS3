#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pile.h"
#include "pile_function.h"

int main ()
{
  Pile *tas;
  char *nom;
  if ((tas = (Pile *) malloc (sizeof (Pile))) == NULL)
    return -1;
  if ((nom = (char *) malloc (50 * sizeof (char))) == NULL)
    return -1;
  initialisation (tas);

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  empiler (tas, nom);
  printf ("La pile (%d éléments): \n",tas->taille);
  printf("\n********** Haut de la PILE **********\n");
  affiche(tas);
  printf("__________ Bas de la PILE __________\n\n");

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  empiler (tas, nom);
  printf ("La pile (%d éléments): \n",tas->taille);
  printf("\n********** Haut de la PILE **********\n");
  affiche(tas);
  printf("__________ Bas de la PILE __________\n\n");

  printf ("Entrez un mot : ");
  scanf ("%s", nom);
  empiler (tas, nom);
  printf ("La pile (%d éléments): \n",tas->taille);
  printf("\n********** Haut de la PILE **********\n");
  affiche(tas);
  printf("__________ Bas de la PILE __________\n\n");

  printf ("\nLe dernier entré (LastInFirstOut) [ %s ] sera supprimé",
                  pile_donnee(tas));
  printf ("\nLe dernier entré est supprime\n");
  depiler (tas);              /* suppression de dernier element entre */
  printf ("La pile (%d éléments): \n",tas->taille);
  printf("\n********** Haut de la PILE **********\n");
  affiche(tas);
  printf("__________ Bas de la PILE __________\n\n");

  return 0;
}

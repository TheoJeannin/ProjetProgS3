void initialisation (Pile * tas){
  tas->debut = NULL;
  tas->taille = 0;
}


int empiler (Pile * tas, char *donnee){
  Element *nouveau_element;
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    return -1;
  if ((nouveau_element->donnee = (char *) malloc (50 * sizeof (char)))
      == NULL)
    return -1;
  strcpy (nouveau_element->donnee, donnee);
  nouveau_element->suivant = tas->debut;
  tas->debut = nouveau_element;
  tas->taille++;
}

int depiler (Pile * tas){
  Element *supp_element;
  if (tas->taille == 0)
    return -1;
  supp_element = tas->debut;
  tas->debut = tas->debut->suivant;
  free (supp_element->donnee);
  free (supp_element);
  tas->taille--;
  return 0;
}

void affiche (Pile * tas){
  Element *courant;
  int i;
  courant = tas->debut;

  for(i=0;i<tas->taille;++i){
    printf("\t\t%s\n", courant->donnee);
    courant = courant->suivant;
  }
}

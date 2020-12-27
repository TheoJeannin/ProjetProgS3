typedef struct ElementListe{
  char *donnee;
  struct ElementListe *suivant;
} Element;

typedef struct ListeRepere{
  Element *debut;
  int taille;
} Pile;


void initialisation (Pile *tas);

int empiler (Pile *tas, char *donnee);

int depiler (Pile *tas);

#define pile_donnee(tas)  tas->debut->donnee

void affiche (Pile *tas);

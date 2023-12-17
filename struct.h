
typedef struct Adherent Adherent;
typedef struct Livre Livre;
typedef struct Emprunt Emprunt;
typedef struct Date Date;

typedef struct Element Element;
typedef struct Elements Elements;
typedef struct Liste Liste;

typedef Element *pointeur;
typedef Elements *pointeurs;
typedef Liste *pointeux;

struct Date{
	int annee;
	int mois;
	int jour;
	int heure;
	int minute;
	int seconde;
};


struct Adherent{
	int index;
	char nom[50];
	char prenom[50];
	int NbEmprunts;
	Date date; 
};

struct Element{
	Adherent pers;
	Element *suivant; 
};


struct Livre{
	int index;
	char Titre[100];
	char Auteur[100];
	int disponible;
	int stock;
};

struct Liste{
	Livre liv;
	Liste *suivant;
};

struct Emprunt{
	int index;
	int id;
	char nom[100];
	char Titre[100];
	char Auteur[100];
	Date date;
	Date retour;
};

struct Elements{
	Emprunt emp;
	Elements *suivant;
};

void menu();

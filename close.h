
void obteni(char *pt){
	char c;
	printf("Desirez vous vraiment quitter l'application (O/N)?: \n");
     	printf("        - O pour Quitter \n");
     	printf("        - N pour retourner a l'application \n");
	do{
		printf("\n\n");
		printf("Entrez votre choix >>");
		fflush(stdin);
		c = toupper(getchar());
	}while(strchr("ON", c) == NULL);
	*pt = c;
}


void traite ( char choix){
	switch(choix){
 		case 'O' : 
                 	   break;break;break;
		case 'N' : menu();
			   break;
		default:
			printf("ceci n'apparait pas dans la liste de choix...");
	}
}
void menu(){
	system("clear");
	char carac;
	Element *liste = malloc(sizeof(*liste));
	Liste *livre = malloc(sizeof(*livre));
	Elements *emprunt = malloc(sizeof(*emprunt));
	char choix ; 
	char n;
    creerFIFO(&liste);
	creerFIFOs(&livre);
	creerFIFOss(&emprunt);
	printf("                    *************************************************\n");
	printf("                    *****   BIENVENUE DANS NOTRE APPLICATION:  ******\n");
	printf("                    *****      GESTION D'UNE BIBLIOTHEQUE      ******\n");
        printf("                    *************************************************\n\n");
	printf("                      - A pour sortir de l'application.\n ");
	printf("                     - B pour les fonctionnalites des adherent.\n ");
	printf("                     - C pour les fonctionnalites des livres.\n");
	printf("                      - D pour les fonctionnalites des emprunts.\n\n\n\n\n\n");
	printf("          Faitez votre choix:  ");
	do{
        	n = toupper(getchar());
        }while( strchr("ABCD",n) == NULL);

        switch(n){
			case 'A':
				do{
					obteni(&choix);   
        				traite(choix) ;   
       				}while (choix != 'O');
				break;
			case 'B':
				do{
					obtenir(&choix);           
        				traiter(choix, &liste) ;   
       				}while (choix != 'Q');
				break;
			case 'C':
				do{
					obtenirs(&choix);           
        				traiters(choix, &livre) ;   
       				}while (choix != 'Q');
				break;
			case 'D':
				do{
					obtenirss(&choix);           
        				traiterss(choix, &emprunt) ;   
       				}while (choix != 'Q');
				break;
			default:
				printf("             Erreur, information inexistante...\n");
				break;
	}

}


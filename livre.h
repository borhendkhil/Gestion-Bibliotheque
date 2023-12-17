
void obtenirs(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouveau livre\n");
     	printf("        - M pour Modifier les informations d'un livre\n");
     	printf("        - S pour Supprimer un livre de la liste\n");
     	printf("        - I pour visualiser la liste Inverse \n");
     	printf("        - R pour retourner au menu principal\n");	
	printf("        - N pour Nettoyer l'ecran \n");
	do{
		printf("\n\n");
		printf("Entrez votre choix >>");
		fflush(stdin);
		c = toupper(getchar());
	}while(strchr("QVCAMSIRN", c) == NULL);
	*pt = c;
}

void affichers(Livre livre){
	printf("\n\nindex:	%5d\n",livre.index);
	printf("nom:	%s\n",livre.Titre);
	printf("prenom:	%s\n",livre.Auteur);
	printf("nombre d'emprunts:	%d\n",livre.disponible);
	printf("Liste d'emprunts:	%d\n",livre.stock);
}

void demanders(Livre *adh){
	Livre perso;
	printf("Entrez les informations d'un livre (les chaines de caractere doivent etre separer par _ ) : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - Titre :  ");
	scanf("%s",perso.Titre);
	viderBuffer();
	printf(" - Auteur :  ");
	scanf("%s",perso.Auteur);
	printf(" - nombre disponible :   ");
	scanf("%d",&(perso.disponible));
	printf(" - le stock total :   ");
	scanf("%d",&(perso.stock));
	*adh = perso;
}

void visualisers( pointeux liste){
	const int parEcran = 20 ;
      	int n ;
      	char unCar ; 

      	n = 0 ;
      	unCar = ' ' ;
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
           	printf("%3d) %d %s %s %d %d \n",n,(liste->liv).index,(liste->liv).Titre, (liste->liv).Auteur,(liste->liv).disponible,
		(liste->liv).stock);

           	liste = liste->suivant;

           	if ( n % parEcran == 0 || liste == NULL){
			printf("\n\n");
             		printf("Appuyez sur Entree pour continuer ou T pour terminer ");
             		fflush(stdin);
             		unCar = toupper(getchar());
             		if (  unCar != 'T' && liste != NULL){    
                   		printf("Dans l'ordre : \n");
              		}
           	}
	}
}

void lires(FILE * donnees, Livre *P){
    	fscanf(donnees,"%d%s%s%d%d \n", &(P->index), P->Titre, P->Auteur, &(P->disponible), &(P->stock));
}

void creerFIFOs(pointeux *L){    
	FILE *donnees ;
     	Livre unePers ;
     	pointeux tempo, Laliste, present ;
     	int tailleOctets = sizeof(Liste) ;
   
     	donnees = fopen("Livre.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeux) malloc (tailleOctets);
         	lires(donnees, &unePers);
         	Laliste->liv = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeux) malloc (tailleOctets);
           		lires(donnees, &unePers);

           		tempo->liv    = unePers ;
           		present->suivant = tempo;
           		present = tempo;
          	}
         	fclose(donnees);
         	present->suivant = NULL; 
     	}
      	*L = Laliste;
}
						

void inversers (pointeux *L){ 
   
	pointeux aContourner, leSuivant , liste = * L ;
   
     	aContourner = liste ;
     	liste        = NULL  ;
   
     	while (aContourner){
		leSuivant            = aContourner->suivant ;

        	aContourner->suivant = liste ;
        	liste                = aContourner ;

        	aContourner          = leSuivant;
       	}

     	*L = liste ;
}



void finds(int aChercher, pointeux liste, pointeux *av, pointeux *cl){
	pointeux avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->liv).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
    
      	if (cestLui && (cestLui->liv).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

void cherchers(pointeux liste){
	pointeux  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numero du livre a chercher ");
        	scanf("%d", &aChercher);
        	finds(aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){  
                	printf("\nYOUPI! on l'a trouve : \n");
                	affichers(cestLui->liv);
          	}else{
          		printf("Desole! on ne trouve pas ce livre\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->liv.index);
         	}
		viderBuffer();
         	printf("avez-vous un autre livre a chercher (O/N) ? ");
       
		
	}while (toupper(getchar()) != 'N');
	viderBuffer();
}

void eliminers( pointeux *P, pointeux avant, pointeux cestLui){
	if(avant == NULL){
	
    		*P = (*P)->suivant ; 
        }else{
		avant->suivant = cestLui->suivant;
	}
}


void supprimers (pointeux *P){
	pointeux liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numero a supprimer ");
       		scanf("%d", &aSupprimer);
       		finds(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouve : \n");
          		affichers(cestLui->liv);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminers( P, avant, cestLui);}
		}else{
          		printf("Desole! on ne trouve pas ce livre\n");
         		viderBuffer();
         		printf("avez-vous autre livre a supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}
void inserers(pointeux *P, Livre unePers, pointeux avant){
	pointeux tempo;

        tempo = (pointeux) malloc(sizeof(Liste));
        tempo->liv = unePers;
        if(avant == NULL){
		tempo->suivant = *P ;
                (*P) = tempo;
        }else{
		tempo->suivant = avant->suivant ;
                avant->suivant= tempo;
              }
}

void ajouters(pointeux *P){
	pointeux liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("Livre.txt","a");
	int aAjouter;
	char reponse ;
      	Livre unePers ;
		viderBuffer();        	
		printf("Entrez le nouveau numero du livre afin de faire une verification d'existance: ");
         	scanf("%d", &aAjouter);
		printf("blablabala");
         	finds(aAjouter, *P, &avant, &cestLui );
        if (cestLui != NULL){
		printf("blablabala");
		viderBuffer();
        	printf("Cet identifiant ou le livre existe deja en: \n");
        	affichers(cestLui->liv);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous ajouter les informations de ce livre avec un autre identifiant ?(O/N) ");
                reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demanders(&unePers);        
		  	inserers(P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d%d ",unePers.index,unePers.Titre,unePers.Auteur,unePers.disponible,unePers.stock);     
		}	
	}
}

void modifiers(pointeux *P){
	pointeux  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Livre nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("Livre.txt","r+");
        do{ 
		viderBuffer();        	
		printf("Entrez le numero du livre a modifier ses informations ");
         	scanf("%d", &aModifier);
         	finds(aModifier, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("On l'a trouve : \n");
        	affichers(cestLui->liv);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous modifier les informations de ce livre ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demanders( &nouvPers);
	                 if ( nouvPers.index == (cestLui->liv).index ){
           		         cestLui->liv = nouvPers;
           		 }else{
                  		eliminers( P, avant, cestLui);
                  		finds( nouvPers.index, *P, &avant, &cestLui);
                  		inserers(P, nouvPers, avant);
			  	fprintf(donnees,"%d %s %s %d%d ",nouvPers.index,nouvPers.Titre,nouvPers.Auteur,nouvPers.disponible,nouvPers.stock);     

                 	 }
            	}
        }else{
        	printf("Desole! on ne trouve pas ce livre\n");
		viderBuffer();
         	printf("avez-vous autre livre a modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      

void traiters( char choix, pointeux *L ){

	switch(choix){
 		case 'V' : visualisers( *L );
                 	   break;
		case 'C' : cherchers( *L );
	                   break ;
		case 'S' : supprimers(L);
	                   break;
		case 'A' : ajouters(L);
	                   break;
		case 'M' : modifiers(L);
	                   break;
		case 'I' : inversers(L); 
	                   visualisers(*L);
          	           inversers(L);
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}


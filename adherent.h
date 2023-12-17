void viderBuffer(){
	int c = 0;
	while (c != '\n' && c != EOF){
		c = getchar();
	}
}

void obtenir(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouvel adherent\n");
     	printf("        - M pour Modifier les informations d'un adherent\n");
     	printf("        - S pour Supprimer un adherent de la liste\n");
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


void afficher(Adherent adherent){
	printf("\n\nindex:	%6d\n",adherent.index);
	printf("nom:	%s\n",adherent.nom);
	printf("prenom:	%s\n",adherent.prenom);
	printf("nombre d'emprunts:	%d\n",adherent.NbEmprunts);
	printf("Date d'inscription:	%d/%d/%d ",adherent.date.annee,adherent.date.mois,adherent.date.jour);

}

void demander(Adherent *adh){
	Adherent perso;
	printf("Entrez les informations de l'adherent : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - nom :  ");
	scanf("%s",perso.nom);
	viderBuffer();
	printf(" - prenom :  ");
	scanf("%s",perso.prenom);
	printf(" - nombre d'emprunts :   ");
	scanf("%d",&(perso.NbEmprunts));
	printf(" - date d'inscription :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.date.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.date.mois));
	printf("\t - annee :");
	scanf("%d",&(perso.date.annee));

	*adh = perso;
}

void visualiser ( pointeur liste){
	const int parEcran = 20 ; 
      	int n ;
      	char unCar ; 

      	n = 0 ;
      	unCar = ' ' ; 
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
           	printf("%3d) %d %s %s %d  %d/%d/%d \n",n,(liste->pers).index,(liste->pers).nom, (liste->pers).prenom,(liste->pers).NbEmprunts,
		(liste->pers).date.annee,(liste->pers).date.mois,(liste->pers).date.jour);

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

void lire (FILE * donnees, Adherent *P){
	Date date;
    	fscanf(donnees,"%d%s%s%d %d%d%d\n", &(P->index), P->nom, P->prenom, &(P->NbEmprunts),&(date.annee),&(date.mois), &(date.jour));
    	P->date  = date;
}


void creerFIFO (pointeur *L){ 
    
	FILE *donnees ;
     	Adherent unePers ;
     	pointeur tempo, Laliste, present ;
     	int tailleOctets = sizeof(Element) ;
   
     	donnees = fopen("Adherent.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeur) malloc (tailleOctets);
         	lire(donnees, &unePers);
         	Laliste->pers = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeur) malloc (tailleOctets);
           		lire(donnees, &unePers);

           		tempo->pers    = unePers ;
           		present->suivant = tempo;
           		present = tempo;
          	}
         	fclose(donnees);
         	present->suivant = NULL; 
     	}
      	*L = Laliste;
}

void inverser (pointeur *L){ 
   
	pointeur aContourner, leSuivant ,liste = * L ;
   
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

void find (int aChercher, pointeur liste, pointeur *av, pointeur *cl){
	pointeur avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->pers).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
  
      	if (cestLui && (cestLui->pers).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

void chercher (pointeur liste){
	pointeur  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numero de la personne a chercher ");
        	scanf("%d", &aChercher);
        	find (aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){    
                	printf("\nYOUPI! on l'a trouve : \n");
                	afficher(cestLui -> pers);
          	}else{
          		printf("Desole! on ne trouve pas cette personne\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->pers.index);
         	}
		viderBuffer();
         	printf("avez-vous une autre personne a chercher (O/N) ? ");
        
		
	}while (toupper(getchar()) != 'N');
	viderBuffer();
}

void eliminer ( pointeur *P, pointeur avant, pointeur cestLui){
	if(avant == NULL){
		
    		*P = (*P)->suivant ; 
        }else{
		avant->suivant = cestLui->suivant;
	}
}

void supprimer (pointeur *P){
	pointeur liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numero a supprimer ");
       		scanf("%d", &aSupprimer);
       		find(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouve : \n");
          		afficher(cestLui->pers);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminer ( P, avant, cestLui);}
		}else{
          		printf("Desole! on ne trouve pas cette personne\n");
         		viderBuffer();
         		printf("avez-vous autre personne a supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}

void inserer (pointeur *P, Adherent unePers, pointeur avant){
	pointeur tempo;

        tempo = (pointeur) malloc(sizeof(Element));
        tempo->pers = unePers ;
        if(avant == NULL){
		tempo->suivant = *P ;
                (*P) = tempo;
        }else{
		tempo->suivant = avant->suivant ;
                avant->suivant= tempo;
              }
}

void ajouter (pointeur * P){
	pointeur liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("Adherent.txt","a");
	int aAjouter;
	char reponse ;
      	Adherent unePers ;
	viderBuffer();        	
	printf("Entrez le nouveau numero de la personne afin de faire une verification d'existance: ");
        scanf("%d", &aAjouter);
        find (aAjouter, *P, &avant, &cestLui );
        reponse = 'N';
        if (cestLui != NULL){
        	printf("Cet identifiant ou personne existe deja en: \n");
        	afficher(cestLui->pers);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous ajouter les informations de cette personne avec un autre identifiant ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demander(&unePers);        
		  	inserer (P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d %d %d %d",unePers.index,unePers.nom,unePers.prenom,unePers.NbEmprunts,
			unePers.date.annee,unePers.date.mois,unePers.date.jour);     
		}	
	}else{
          	printf("Cet identifiant n'existe pas\n");
          	printf("Ajoutez les informations de cette personne,Tapez O ?");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demander(&unePers);        
		  	inserer (P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d %d %d %d",unePers.index,unePers.nom,unePers.prenom,unePers.NbEmprunts,
			unePers.date.annee,unePers.date.mois,unePers.date.jour);     
		}	
	}
}


void modifier (pointeur * P){
	pointeur  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Adherent nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("Adherent.txt","r+");

        do{
	viderBuffer();        	
	printf("Entrez le numero de la personne a modifier ses informations ");
        scanf("%d", &aModifier);
 
         	find(aModifier, *P, &avant, &cestLui );

        if (cestLui != NULL){
        	printf("On l'a trouve : \n");
        	afficher(cestLui->pers);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous modifier les informations de cette personne ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demander( &nouvPers);
	                 if ( nouvPers.index == (cestLui->pers).index ){
           		         cestLui->pers = nouvPers;
           		 }else{
                  		eliminer ( P, avant, cestLui);
                  		find ( nouvPers.index, *P, &avant, &cestLui);
                  		inserer(P, nouvPers, avant);
			  	fprintf(donnees,"%d %s %s %d %d %d %d",nouvPers.index,nouvPers.nom,nouvPers.prenom,nouvPers.NbEmprunts,
				nouvPers.date.annee,nouvPers.date.mois,nouvPers.date.jour);     
				viderBuffer();
                 	 }
            	}
		}else{
        	printf("Desole! on ne trouve pas cette personne\n");
		viderBuffer();
         	printf("avez-vous autre personne a modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      

void traiter ( char choix, pointeur * L ){
 
	switch(choix){
 		case 'V' : visualiser( *L );
                 	   break;
		case 'C' : chercher ( *L );
	                   break ;
		case 'S' : supprimer (L);
	                   break;
		case 'A' : ajouter (L);
	                   break;
		case 'M' : modifier(L);
	                   break;
		case 'I' : inverser(L); 
	                   visualiser(*L);
          	           inverser(L); 
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}


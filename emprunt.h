
void obtenirss(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouvel emprunt\n");
     	printf("        - M pour Modifier les informations d'un emprunt\n");
     	printf("        - S pour Supprimer un emprunt de la liste\n");
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

void afficherss(Emprunt emprunt){
	printf("\n\nindex:	%6d\n",emprunt.index);
	printf("l'identifiant de l'adherent:    %d\n",emprunt.id);
	printf("nom adherent:	%s\n",emprunt.nom);
	printf("Titre de l'ouvrage:	%s\n",emprunt.Titre);
	printf("Auteur de l'ouvrage:	%s\n",emprunt.Auteur);
	printf("Date d'emprunt:	%d/%d/%d  %d:%d \n",emprunt.date.annee,emprunt.date.mois,emprunt.date.jour,emprunt.date.heure,emprunt.date.minute);
	printf("Date retour:	%d/%d/%d  %d:%d \n",emprunt.retour.annee,emprunt.retour.mois,emprunt.retour.jour,emprunt.retour.heure,emprunt.retour.minute);
}

void demanderss(Emprunt *emp){
	Emprunt perso;
	printf("Entrez les informations de l'emprunt : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - identifiant adherent:   ");
	scanf("%d",&(perso.id));
	fflush(stdin);
	viderBuffer();
	printf(" - nom adherent:  ");
	scanf("%s",perso.nom);
	viderBuffer();
	printf(" - Titre de l'ouvrage :  ");
	scanf("%s",perso.Titre);
	viderBuffer();
	printf(" - Auteur de l'ouvrage :  ");
	scanf("%s",perso.Auteur);
	printf(" - date d'emprunt :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.date.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.date.mois));
	printf("\t - annee :");
	scanf("%d",&(perso.date.annee));
	printf("\t - heure :");
	scanf("%d",&(perso.date.heure));
	printf("\t - minute :");
	scanf("%d",&(perso.date.minute));
	printf(" - date de retour :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.retour.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.retour.mois));
	printf("\t - annee :");
	scanf("%d",&(perso.retour.annee));
	printf("\t - heure :");
	scanf("%d",&(perso.retour.heure));
	printf("\t - minute :");
	scanf("%d",&(perso.retour.minute));
	*emp = perso;
}

void visualiserss(pointeurs liste){
	const int parEcran = 20 ;
      	int n ;
      	char unCar ; 

      	n = 0 ;
      	unCar = ' ' ;
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
		printf("%3d) %d %d %s %s %s   %d/%d/%d %d:%d  %d/%d/%d %d:%d \n",n,(liste->emp).index,(liste->emp).id,(liste->emp).nom, (liste->emp).Titre,(liste->emp).Auteur,
		(liste->emp).date.annee,(liste->emp).date.mois,(liste->emp).date.jour,(liste->emp).date.heure,(liste->emp).date.minute,
		(liste->emp).retour.annee,(liste->emp).retour.mois,(liste->emp).retour.jour,(liste->emp).retour.heure,(liste->emp).retour.minute);

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

void liress (FILE * donnees, Emprunt *P){
	Date date;
	Date retour;
    	fscanf(donnees,"%d%d%s%s%s %d%d%d%d%d %d%d%d%d%d\n", &(P->index), &(P->id), P->nom, P->Titre, P->Auteur,&(date.annee),&(date.mois), 
		&(date.jour),&(date.heure),&(date.minute),&(retour.annee),&(retour.mois),&(retour.jour),&(retour.heure),&(retour.minute));
    	P->date  = date;
	P->retour  = retour;
}


void creerFIFOss (pointeurs *L){ 
	FILE *donnees ;
     	Emprunt unePers ;
     	pointeurs tempo, Laliste, present ;
     	int tailleOctets = sizeof(Elements) ;
   
     	donnees = fopen("Emprunt.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeurs) malloc (tailleOctets);
         	liress(donnees, &unePers);
         	Laliste->emp = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeurs) malloc (tailleOctets);
           		liress(donnees, &unePers);

           		tempo->emp    = unePers ;
           		present->suivant = tempo;
           		present = tempo;
          	}
         	fclose(donnees);
         	present->suivant = NULL; 
     	}
      	*L = Laliste;
}
						

void inverserss(pointeurs *L){ 
   
	pointeurs aContourner, leSuivant , liste = * L ;
   
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

void findss(int aChercher, pointeurs liste, pointeurs *av, pointeurs *cl){
	pointeurs avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->emp).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
 
      	if (cestLui && (cestLui->emp).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

void chercherss(pointeurs liste){
	pointeurs  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numero de la personne a chercher ");
        	scanf("%d", &aChercher);
        	findss (aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){  
                	printf("\nYOUPI! on l'a trouve : \n");
                	afficherss(cestLui->emp);
          	}else{
          		printf("Desole! on ne trouve pas cet emprunt\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->emp.index);
         	}
		viderBuffer();
         	printf("avez-vous un autre emprunt a chercher (O/N) ? ");
         
		
	}while (toupper(getchar()) != 'N');
	viderBuffer();
}

void eliminerss(pointeurs *P, pointeurs avant, pointeurs cestLui){
	if(avant == NULL){
		
    		*P = (*P)->suivant ;
        }else{
		avant->suivant = cestLui->suivant;
	}
}


void supprimerss(pointeurs *P){
	pointeurs liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numero a supprimer ");
       		scanf("%d", &aSupprimer);
       		findss(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouve : \n");
          		afficherss(cestLui->emp);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminerss( P, avant, cestLui);}
		}else{
          		printf("Desole! on ne trouve pas cet emprunt\n");
         		viderBuffer();
         		printf("avez-vous autre emprunt a supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}

void insererss(pointeurs *P, Emprunt unePers, pointeurs avant){
	pointeurs tempo;

        tempo = (pointeurs) malloc(sizeof(Elements));
        tempo->emp = unePers ;
        if(avant == NULL){
		tempo->suivant = *P ;
                (*P) = tempo;
        }else{
		tempo->suivant = avant->suivant ;
                avant->suivant= tempo;
              }
}

void ajouterss(pointeurs * P){
	pointeurs liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("Emprunt.txt","a");
	int aAjouter;
	char reponse ;
      	Emprunt unePers ;
		viderBuffer();        	
		printf("Entrez le nouveau numero de l'emprunt afin de faire une verification d'existance: ");
         	scanf("%d", &aAjouter);
         	findss(aAjouter, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("Cet identifiant ou emprunt existe deja en: \n");
        	afficherss(cestLui->emp);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous ajouter les informations de cet emprunt avec un autre identifiant ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demanderss(&unePers);        
		  	insererss(P, unePers, avant);
		  	fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",unePers.index,unePers.id,unePers.nom,unePers.Titre,unePers.Auteur,
			unePers.date.annee,unePers.date.mois,unePers.date.jour,unePers.date.heure,unePers.date.minute,
			unePers.retour.annee,unePers.retour.mois,unePers.retour.jour,unePers.retour.heure,unePers.retour.minute);     
		}	
	}else{
          	printf("Cet identifiant n'existe pas\n");
          	printf("Tapez O pour l'ajout des informations de cet emprunt ");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
				viderBuffer();
	        	demanderss(&unePers);        
				insererss(P, unePers, avant);
				fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",unePers.index,unePers.id,unePers.nom,unePers.Titre,unePers.Auteur,
				unePers.date.annee,unePers.date.mois,unePers.date.jour,unePers.date.heure,unePers.date.minute,
				unePers.retour.annee,unePers.retour.mois,unePers.retour.jour,unePers.retour.heure,unePers.retour.minute);     
			}
			
	}
}

void modifierss(pointeurs * P){
	pointeurs  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Emprunt nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("Emprunt.txt","r+");
        do{ 
		viderBuffer();        	
		printf("Entrez l'identifiant de l'emprunt a modifier ses informations ");
         	scanf("%d", &aModifier);
         	findss(aModifier, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("On l'a trouve : \n");
        	afficherss(cestLui->emp);
          	printf("\n\n");
		viderBuffer();
          	printf("Desirez-vous modifier les informations de cet emprunt ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demanderss( &nouvPers);
	                 if ( nouvPers.index == (cestLui->emp).index ){
           		         cestLui->emp = nouvPers;
           		 }else{
                  		eliminerss( P, avant, cestLui);
                  		findss( nouvPers.index, *P, &avant, &cestLui);
                  		insererss(P, nouvPers, avant);
			  	fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",nouvPers.index,nouvPers.id,nouvPers.nom,nouvPers.Titre,
				nouvPers.Auteur,nouvPers.date.annee,nouvPers.date.mois,nouvPers.date.jour,nouvPers.date.heure,nouvPers.date.minute,
				nouvPers.retour.annee,nouvPers.retour.mois,nouvPers.retour.jour,nouvPers.retour.heure,nouvPers.retour.minute);     

                 	 }
            	}
        }else{
        	printf("Desole! on ne trouve pas cet emprunt\n");
		viderBuffer();
         	printf("avez-vous autre emprunt a modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      

void traiterss( char choix, pointeurs *L){
	switch(choix){
 		case 'V' : visualiserss( *L );
                 	   break;
		case 'C' : chercherss( *L );
	                   break ;
		case 'S' : supprimerss(L);
	                   break;
		case 'A' : ajouterss(L);
	                   break;
		case 'M' : modifierss(L);
	                   break;
		case 'I' : inverserss(L); 
	                   visualiserss(*L);
          	           inverserss(L); 
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}


	//START OF PROTOTYPES
	bool affectationSimple(Element * tmpProg);
	bool LireAffectation(Element *tmpProg);
	bool ecrireAffectation(Element * tmpProg);
	int ChartoIntiger(char * nbrTypeChar);
	void interpretation();
	Element * Si(Element * tmpProg);
	Element* interpretationInnerSi(Element *tmpProg);
	//END OF PROTOTYPES
				
			/*********************************************************************/
							//INTERPRETATION
			/*********************************************************************/	
void interpretation(Element *tmpProg){
	// LA LISTE DES caracteres et entier EST DEJA GLOBALE
	ElementInt  *tmpListInt = ListOfEntier;
	ElementChar *tmpListChar = ListOfCharactere;

	
	while(tmpProg!=NULL) {

		if(strcmp(tmpProg->data,"lire")==0){
			LireAffectation(tmpProg);
		
		}else if(strcmp(tmpProg->data,"ecrire")==0){
			ecrireAffectation(tmpProg);		
		}
		else if(tmpProg->next!=NULL){	//  si tmpProg->next == null ,tmpProg->next->data va planter le prog
			if(strcmp(tmpProg->next->data,":=")==0){
			
				affectationSimple(tmpProg);	
			}	
		}
		 if(strcmp(tmpProg->data,"si")==0){
		
			tmpProg = Si(tmpProg);	//J'AI MIS SI ICI CAR JE DOIS TESTER LA VAL DU VAR x avec la val du var y , si ( x > y ) exmple
		}
		
	
tmpProg=tmpProg->next;
	}
	
}
			/*********************************************************************/
							//INTERPRETATION
			/*********************************************************************/	
Element* interpretationInnerSi(Element *tmpProg){
	// LA LISTE DES caracteres et entier EST DEJA GLOBALE
	ElementInt  *tmpListInt = ListOfEntier;
	ElementChar *tmpListChar = ListOfCharactere;


	while(tmpProg!=NULL) {
		if(strcmp(tmpProg->data,"lire")==0){
			LireAffectation(tmpProg);
		
		}else if(strcmp(tmpProg->data,"ecrire")==0){
			ecrireAffectation(tmpProg);		
		}
		else if(tmpProg->next!=NULL){	//  si tmpProg->next == null ,tmpProg->next->data va planter le prog
			if(strcmp(tmpProg->next->data,":=")==0){
			
				affectationSimple(tmpProg);	
			}	
		}
		 if(strcmp(tmpProg->data,"sinon")==0 || tmpProg->data[0]==';'){
		
			return tmpProg;	//J'AI MIS SI ICI CAR JE DOIS TESTER LA VAL DU VAR x avec la val du var y , si ( x > y ) exmple
		}
		
	
tmpProg=tmpProg->next;
	}
	printf("\nwarning fro inter inner si");
	return tmpProg ; //warning
}


int ChartoIntiger(char * nbrTypeChar){
    int  valeur=0, longueur, i, disainne=1;

    longueur = strlen(nbrTypeChar);
    for( i=0;i<longueur;i++){
        valeur += disainne*(nbrTypeChar[longueur-1-i] - 48);
        disainne= 10*disainne;
    }
    // printf("%d ",valeur);
     return valeur;
//return -1; // Value isn't intiger
}
	
			/*********************************************************************/
							//LIRE AFFECTATION
			/*********************************************************************/		
bool LireAffectation(Element *tmpProg){
	ElementChar *tmpChar=ListOfCharactere;
	ElementInt *tmpInt =ListOfEntier;
	
	while(tmpChar!=NULL){fflush(stdin);
		
			if(tmpProg->next->next->data[0] == tmpChar->nom ){	//
				printf("\nADMINE MESSAGE ENTER VALUE FOR %c\t",tmpChar->nom) ; // retour a la ligne dans terminal tjr avant q'il lire une valeur apartir du terminal
				scanf("%c",&tmpChar->valeur);
			//	printf("\nThe ACTUAL VALUE IS OF %c IS \t %c",tmpChar->nom,tmpChar->valeur);
				return true;
			}
		
	tmpChar = tmpChar->next;
	}
	
	while(tmpInt){
				if(tmpProg->next->next->data[0] == tmpInt->nom ){
					printf("\nADMINE MESSAGE ENTER VALUE FOR %c\t",tmpInt->nom ); // retour a la ligne dans terminal tjr avant q'il lire une valeur apartir du terminal
					 scanf("%d",&tmpInt->valeur);
				//	 printf("\nTHE ACTUAL VALUE OF %c IS %d",tmpInt->nom,tmpInt->valeur);
					return true;
				}
	tmpInt = tmpInt->next;									
	}
	return false;
}
			/*********************************************************************/
							// AFFECTATION	SIMPLE
			/*********************************************************************/	
bool affectationSimple(Element * tmpProg){
	ElementChar *tmpChar=ListOfCharactere;
	ElementInt *tmpInt =ListOfEntier;
	bool tmp;
	while(tmpChar!=NULL){						//tmp->next : dat[0]= ' , data[1] = valeur , data[2] = '
		if(tmpChar->nom == tmpProg->data[0]){
			tmpChar->valeur =tmpProg->next->next->data[1] ;
			printf("\nThe ACTUAL VALUE  OF %c IS \t %c",tmpChar->nom,tmpChar->valeur);
			return 1;
		}
	tmpChar = tmpChar->next;
	}
	
	while(tmpInt!=NULL){
		if(tmpProg->data[0]==tmpInt->nom){
			tmpInt->valeur = ChartoIntiger(tmpProg->next->next->data);
			printf("\nTHE ACTUAL VALUE OF %c IS %d",tmpInt->nom,tmpInt->valeur);	
			return 1;							
		}
	tmpInt = tmpInt->next;
	}
}

			/*********************************************************************/
							// ECRIRE AFFECTATION
			/*********************************************************************/	
bool ecrireAffectation(Element * tmpProg){
	ElementChar *tmpChar=ListOfCharactere;
	ElementInt *tmpInt =ListOfEntier;
	while(tmpChar){
		if(tmpProg->next->next->data[1] == tmpChar->nom ){	
			printf("\nThe ACTUAL VALUE IS OF %c IS \t %c",tmpChar->nom,tmpChar->valeur);
			return true;
		}											
	tmpChar= tmpChar->next;
	}
	while(tmpInt){
	
		if(tmpProg->next->next->data[0] == tmpInt->nom ){
			printf("\nTHE ACTUAL VALUE OF %c IS %d",tmpInt->nom,tmpInt->valeur);
			return true;
		}										
	tmpInt=tmpInt->next;
	}
return 0;
}

			/*********************************************************************/
							//LA FONCTION Si FONCTIONNEMENT
			/*********************************************************************/
Element * Si(Element * tmpProg){		//JE VAIS TRAVAILLER COMME J'AI SI ( X > Y )
	ElementChar *tmpChar=ListOfCharactere;
	ElementInt *tmpInt =ListOfEntier;
	char x 	      = tmpProg->next->next->data[0],
		operateur = tmpProg->next->next->next->data[0],
		y 		  = tmpProg->next->next->next->next->data[0];
	int xValue=0;
	int yValue=0 ;
				//Je vais chercher la val de x dans les listes des variables(lest des entiers et list des caracteres) stocké
	//printf("\n %c %c %c",x,operateur,y);
		while (tmpChar){
			if(tmpChar->nom == x){
			xValue = tmpChar->valeur;
			}
		tmpChar=tmpChar->next;	
		}
		
		while(tmpInt){
			if(tmpInt->nom == x){
				xValue = tmpInt->valeur;
			}
		tmpInt=tmpInt->next;	
		}
		tmpChar=ListOfCharactere;
				//Je vais chercher la val de y dans les listes des variables (lest des entiers et list des caracteres) stocké	

		tmpChar=ListOfCharactere;	// rendre les variables temporaire point sur les debuts des listes (lest des entiers et list des caracteres)
		tmpInt =ListOfEntier;	

		while(tmpInt){
			if(tmpInt->nom == y){
				yValue = tmpInt->valeur;
			}
		tmpInt=tmpInt->next;	
		}
		while(tmpChar){
			if(tmpChar->nom == y){
				yValue = tmpChar->valeur;
			}
		tmpChar=tmpChar->next;
		}
								//APRES QUE J'AI TROUVER LES VALEURS DE x et y JE VAIS SELECTIONNER L'OPERATION
		if(operateur =='>')	{
			if( xValue > yValue){
				
				//printf("\nTRUE %c %c %c",x,operateur,y);
			
			tmpProg =interpretationInnerSi(tmpProg);		
			if(tmpProg->data[0]==';'){
					return tmpProg;
				}else{
					while(tmpProg->data[0]!=';'){
						tmpProg = tmpProg->next;
					}
					return tmpProg;
				}
			}else{
			//	printf("\nFALSE %c < %c",x,y);
				while(tmpProg->data[0]!=';' &&strcmp(tmpProg->data,"sinon")!=0){
					tmpProg = tmpProg->next;
				}
				return tmpProg;
			}	
		}
			
		if(operateur =='=')	{
			if( xValue == yValue){
				
			//	printf("\nTRUE %c %c %c",x,operateur,y);	
				tmpProg =interpretationInnerSi(tmpProg);
				if(tmpProg->data[0]==';'){
					return tmpProg;
				}else{
					while(tmpProg->data[0]!=';'){
						tmpProg = tmpProg->next;
					}
					return tmpProg;
				}		
			}else{
			//	printf("\nFALSE %c < %c",x,y);
				while(tmpProg->data[0]!=';' &&strcmp(tmpProg->data,"sinon")!=0){
			

					tmpProg = tmpProg->next;
				}
				return tmpProg;
			}	
		}
		
		if(operateur =='<')	{
			if( xValue < yValue){		
		//	printf("\nTRUE %c %c %c",x,operateur,y);
				
			tmpProg =interpretationInnerSi(tmpProg);		
			if(tmpProg->data[0]==';'){
					return tmpProg;
			}else{
					while(tmpProg->data[0]!=';'){
						tmpProg = tmpProg->next;
					}
				return tmpProg;
			}		
			
			}else{
		//		printf("\nFALSE %c < %c",x,y);
				while(tmpProg->data[0]!=';' &&strcmp(tmpProg->data,"sinon")!=0){
					tmpProg = tmpProg->next;
				}
				return tmpProg;
			}	
		}	
}


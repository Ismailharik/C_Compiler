int CheckIfNameOfVarExisted(char NewVar){
	
    ElementChar *tmpChar = ListOfCharactere;
    ElementInt *tmpInt = ListOfEntier;
	
	//JE DOIS CHECRCHER  DANS LA LIST DES CARACTERE
    while(tmpChar!=NULL){
        if(tmpChar->nom==NewVar){
            return 1;
        }  
		tmpChar = tmpChar->next;
    }
   	//JE DOIS CHECRCHER  DANS LA LIST DES ENTIERS
    while(tmpInt!=NULL){
        if(tmpInt->nom==NewVar){
            return 1;
        }  
		tmpInt = tmpInt->next;
    }
    
return 0;     //lE PROGRAMME ARRIVE A LA FIN SEULEMENT DANS LE CAS OU LE VAR N'EXISTE DANS AUCUNE LISTE
}

							//****************************************
								// ANALYSE SEMANTIQUE
							//****************************************

int AnalyseSem(Element *localFile ){ 
//	printf("\nFROM ANAL SEM");
if(strcmp(localFile->data,"variable")==0)		//pour les declarations
{
	char   *type=localFile->next->next->data,
	 		nom = *localFile->next->data ;
	int ligne = localFile->ligne;

	 	// printf("\n nom %c Type %s ", nom, type);	 	
	if(strcmp( type, "caractere")==0){	//TRAITEMENT DES VARIABLES  CARACTERES
		if(! CheckIfNameOfVarExisted(nom)){					
		//	printf("\n ce var est un nv var");
			ListOfCharactere= emfilerChar(ListOfCharactere,nom );	//emFilerInt c'est la fct qui reserve une espace memoire pour le var actuel
			return 1;
		}else{
	 		printf("\nErreur Sem : redeclaration du var %c voir ligne %d ", nom,ligne);
	 		return 0;	//probleme de redeclaration
		}
	}
	
	if(strcmp( type, "entier")==0){		//TRAITEMENT DES VARIALES ENTIERES
		if(! CheckIfNameOfVarExisted(nom)){		//SI CE VAR EST UN NV VARIABLES(CàD n'est pas deja declarer) JE JA L'AJOUTER AVEC LES VARIABLES			
		//	printf("\n ce var est un nv var");
			ListOfEntier= emFilerInt(ListOfEntier,nom );	//emFilerInt c'est la fct qui reserve une espace memoire pour le var actuel
			return 1;
		}else{
	 		printf("\nErreur Sem : redeclaration du var %c voir ligne %d ", nom,ligne);
	 		return 0;	//probleme de redeclaration
		}
	}
}
else{		//POUR LES AFFECTATION
		
		if(!CheckIfNameOfVarExisted(localFile->data[0])){
			printf("\nErreur Sem : %c Undeclared",localFile->data[0]);
			return 2; // ce var undeclared
		}
	}	 
 	
}






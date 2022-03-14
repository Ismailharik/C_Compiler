				//DEEFINITION DES FONCTIONS
				int comparerList( char *s);
				Element* ConvertFileToList(FILE *ProgFile,Element *Debut, int  ligneP);
				//FIN DEFINITIONS DES FONCTIONS

				/*******************************************************************************************/
											//Starting Analyse Lexical 
				/*******************************************************************************************/

bool analyser_lix(){

	int i=0;
	char c1, *c2, mot[10];
	FILE * ProgFile = fopen("programme.txt","r");
	FILE * DictFile = fopen("dictionnaire.txt","r");
	FILE *ErrorFile = fopen("ErrorFile.txt","w");
	Element *L1,*L2;
	Element *maFile=NULL;				 // lA FILE QUI VA TRAITER CHAQUE LIGNE
	bool tmpSyntaxique = true, tmpSemantique =true,tmpLexical=true ;	 	// tmpSemantique S'IL Y A UN PROBLEME DANS L'ANA SEMANTIQUE , resp tmpSyntaxique et tmpLexical
	int ligneP=1,ligneD=1,detectLigne=0 , returOfAnSem=0;	

	L1=ProgList=ConvertFileToList(ProgFile,ProgList,ligneP);	//L1 L2 DES VARIALES TEMPORAIRES POUR PARCOURIR LA LIST , ProgList et DictList sont declarer globalement , 
	L2=DictList=ConvertFileToList(DictFile,DictList,ligneD);	//ils seront pointer tjrs sur les debut de la list

while(L1!=NULL){
        if(comparerList(L1->data)){		// LA FCT comparerList prend dans l'entrer une chaine et la chercher dans le dictionnaire , s'il exist la fct return 1 sinon 0
            //printf("\n |%s| existed voir ligne %d",L1->data, L1->ligne);
            maFile = emFiler(maFile, L1->ligne,L1->data); 	//maFile EST UNE FILE QUI STOCK UN LIGNE ET LEUR EMPLACEMENT
            if(detectLigne+2<=L1->ligne  ){	//comme ca je savoir s'il y a un saut de ligne
                //detectLigne++;				//JE DOIS l'AUGMENTER PAR 1, POUR QUI'IL RESTE TOUJOURS INFERIEUR A LA LIGNE ACTUEUL PAR 1
               detectLigne = L1->ligne -1;
			   // afficher(maFile);
                
				tmpSyntaxique =AnalyseSyn(maFile);	//APRES QUI'IL SE TERMINE CHAQUE LIGNE JE LE PASSE AU TRAITEMENT DE L'ANALYSE SYNTAXIQUE
                
                if(strcmp(maFile->data,"variable")==0){		//APRES QUE JE FINI LE TRAITEMNT DE L'ANALUSE SYNTAXIQUE , JE PASSE CE LIGNE AU TRAITEMENT DE L'ANALYSE SEMANTIQUE
					 returOfAnSem=AnalyseSem(maFile);	//LA FCT AnalyseSem RETURN 1 SI L'ANA SEM EST CORRECT , 0 S'IL Y A UN PROB DE REDECLARATION , 2 S'IL YA UN PROB DE LA REDECLARATION
					if( returOfAnSem!=1){
						tmpSemantique=false;			
					}			
				}

				if(maFile->next!=NULL){							//JE VERIFIE SI LE NEXT EST != 0 PAR CE QUE JE VAIS TESTER next->data SI NEXT EST NULL JE PROGRAMME SERA PLANTER
					if(strcmp(maFile->next->data,":=")==0){		//COMME CA JE SAVOIR SI UN LIGNE CONTIENT UNE AFFECTATION
						
						 returOfAnSem=AnalyseSem(maFile);		//returOfAnSe	0 si le prob de redeclaration , 2 affectation a un var undeclared
						if(returOfAnSem!=1){	
							tmpSemantique=false;									
						}			
					}	
			}
			maFile=NULL;	
		    }
        }else{
            printf("\nErreur LEXICAL : le mot %s n'existe pas. voir ligne %d",L1->data,L1->ligne);
            tmpLexical = false;
			fprintf(ErrorFile,"%s\n",c1);
        }
L1 = L1->next;
}

						
return  tmpLexical&&tmpSemantique&&tmpSyntaxique; //le return de tout les fcts 

}

					//**************************************************************************
					                    //COMPARER UN MOT AVEC UNE LIST
					//**************************************************************************
int comparerList( char *s){
        Element *tmpDict=DictList;
      int i;  
        //Ce if est speciallement pour accepter les affectations  ou les val des affect dans le programmes , Par EX a := 's'
       if(s[0]=='\'' &&(s[1]>=0 )&&(s[1]<=122 ) &&s[2]=='\''|| s[0]==':'&&s[1]=='='){
           	return 1;
		}
		//Ce if est speciallement pour accepter les noms des var ( les alphabets maj et minusclue)
		 if((s[0]>=97 )&&(s[0]<=122 ) && s[1]=='\0' ||(s[0]>=41 )&&(s[0]<=90 ) && s[1]=='\0'  ){	//Pour accepter tout les noms de variables
           	return 1;
		}
        //Ce if est speciallement pour accpter les nbr, je la besoins dans les valeurs des variables entiers	
		for( i=0;i<strlen(s)-1;i++){
		 if((s[i]>=48 )&&(s[i]<=57 ) ){	
            	return 1;
			} 	
		}
								//comparer la chaine avec le dictionnaire
        while(tmpDict!=NULL){

            if(strcmp(tmpDict->data,s)==0){
            //    printf("\nle mot %s exist",L2->data);
                return 1;
            }
            tmpDict= tmpDict->next;
        }
return 0;
}

					//**************************************************************************
					                    //CONVERTIR FICHIER A LIST
					//**************************************************************************
Element* ConvertFileToList(FILE *ProgFile,Element *Debut, int  ligneP){
	char c1,prev=' ',mot[10];
	int i=0;
while(!feof(ProgFile)){
restart:
  c1  = (char)fgetc(ProgFile);
  
	//POUR Q'IL N'ACCEPT PAS LES TABULATIONS
	while(c1=='\t'){			
	  	c1 =fgetc(ProgFile);
	}
	//CE IF POUR LES COMMENTAIRE
  if(c1==47){	//92 le code asci de /
  
	  	if(prev==' '){
	  		prev=47;// CAD pev= \	
	  		goto restart;
		}else if (prev==47 && c1==47){
			do{	
				c1=(char)fgetc(ProgFile);
			}while(c1!='\n');		
		}
   }
  	//FIN TRAITEMENT DES COMMENTAIRES
  	
  	// Lating our programme showing ecrire ( " efrgrgbbg " ) ;
  if(c1=='.') break;
 if(c1=='\n'){
        ligneP++;
        mot[i]='\0';
        i=0;
     //   printf("\n %s dans la ligne %d",mot,ligneP);
      if(mot[0]!='\0' )
        Debut = emFiler(Debut,ligneP,mot); 
      }
   
   	else if(c1==' '){
      mot[i]='\0';
       //  printf("\n%s dans la ligne %d",mot,ligneP);
      i=0;
      	if(mot[0]!='\n'&&mot[0]!=' '&&mot[0]!='\0' ){
      		Debut = emFiler(Debut,ligneP,mot);
	  	}
      
    }
    else if(c1==';'){// il doit stoper s 'il trouve aussi un ;
    	mot[i]=';';
    	mot[i+1]='\0';
    	Debut = emFiler(Debut,ligneP,mot);
	}
	else{
    mot[i++]=c1;
    } 
    
}
return Debut;

}

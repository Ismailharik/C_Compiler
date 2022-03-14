bool AnalyseSyn(Element *localFile){
	bool tmp = true;
	int AnSynReturn;
	if(localFile!=NULL){	
					
		if(strcmp(localFile->data,"lire")==0){	
		AnSynReturn = Analyse_Syn_lire(localFile);
			if(AnSynReturn!=1){
				printf("\nFROM AN SYN  | LIRE: false");
				tmp = false;	
			}
		}else if(strcmp(localFile->data,"si")==0){	
		AnSynReturn =Analyse_Syn_Si(localFile);
			if(AnSynReturn!=1){
				printf("\nFROM AN SYN | SI:false");
				tmp = false;	
			}	
		}else if (strcmp(localFile->data,"ecrire")==0){
		AnSynReturn =Analyse_Syn_ecrire(localFile);
			if(AnSynReturn!=1){
				printf("\nFROM AN SYN | ECRIRE: false");
				tmp = false;	
			}
		}else if(strcmp(localFile->data,"variable")==0 ){
		AnSynReturn =Analyse_Syn_variable(localFile);
			if(AnSynReturn!=1){
				printf("\nFROM AN SYN | VARIABLE: false");
				tmp = false;	
			}	
		}else if(AnSynReturn=verifierLaffectation(localFile)){	//si il y a une affect cette fct va retourner une val !=0 ,le return c'est le type d'erreur
																//la meme fct return quel erreur de l'erreur
			if(AnSynReturn!=1){
				printf("\nfalse");
				tmp = false;	
			}
		}
		if(!tmp){
	
			switch(AnSynReturn){
									
				case 0 : printf("\n#####Erreur SYN: manque d'une ( , voir ligne %d", localFile->ligne);
				break;
			//						case 1 : printf("Succes");
			//						break;
				case 2: printf("\n#####Erreur SYN: manque d'une ) , voir ligne %d", localFile->ligne);
				break;
				case 3 : printf("\n#####Erreur SYN: manque d'une ; , voir ligne %d", localFile->ligne);
				break;
				case 4:  printf("\n#####Erreur SYN: manque d'un variable , voir ligne %d", localFile->ligne);
				break;
				case 5 : printf("\n#####Erreur SYN: manque d'un operateur', voir ligne %d", localFile->ligne);
				break;
				case 6 : printf("\n#####Erreur SYN: manque d'une \" , voir ligne %d", localFile->ligne);
				break;
				case 7 : printf("\n#####Erreur SYN: declarer un type de variable, voir ligne %d", localFile->ligne);
				break;
				case 8 : printf("\n#####Erreur SYN: le synthax d'ecrire est similaire , voir ligne %d", localFile->ligne);
				break;
				case 9 : printf("\n#####Erreur SYN: manque d'une valeur, voir ligne %d", localFile->ligne); 
				break;
				case 10 : printf("\n#####Erreur SYN: manque de alors ,voir ligne %d", localFile->ligne);
				break;
				case 11 : printf("\n#####Erreur SYN: manque de finsi , voir ligne %d", localFile->ligne);
				break;
				//	default : printf("\nThere is a problem or return is 1");							
			}
		}
	}else{
	printf("\n the local file is null in analyse sem");
	}
return tmp;
}

				/*******************************************************************************************/
											//Starting Analyse Syntaxique   ###LIRE###
				/*******************************************************************************************/
				
int Analyse_Syn_lire(Element * localFile){
	char c, tab[10]="lire";

//printf("\n######SNY FILE S=%s tab=%s", s,tab);

if(strcmp(localFile->data,tab)==0){
	
	localFile=defiler(localFile);
	if(localFile!=NULL){
			
				if(*localFile->data=='('){
						
					localFile=defiler(localFile);
					if(localFile!=NULL){
							if( *localFile->data>=97 && *localFile->data<=122){
														//Je dois passe le char  par curseur 
								if(localFile!=NULL){
										localFile=defiler(localFile);     	// a ce moment la j'ai defiler le var
								}else{
									return 2; // Manque d'une par fermante
								}	
							}else {
								return 4; 		//Monque d'un variable
							}
					
							// L'autre moitier de la ligne
							
								
							if(localFile!=NULL){
								if(*localFile->data==')' ){	
									if(localFile!=NULL){
										localFile = defiler(localFile);
										if(localFile!=NULL){
									
											if(*localFile->data==';'){ 
											localFile = defiler(localFile);
												return 	1; 			//Alhamdulilah SYN Successful
											}else{
												return 3; // il vas retourner un 3 s'il ne trouve pas un ;
											}
											
										}else{
											return 3; // il vas retourner un 3 s'il ne trouve pas un ;
										}
										}else{
											return 3; // il vas retourner un 3 s'il ne trouve pas un ;
										}					
								} else{ 
									return 2; // il vas retourner un 2 lorsqu'il manque d'une parenthese fermante
								}
							}else{
									return 2; //
							}	
				}else{
					return 4; // lorsqu'il manque d'un var
				}
			
		}else{
			return 0; // lorsqu'il manque d'une parenthese ouvrante
	
		}

	}else{
			return 0;
	}
}else{
	return -1;
}
}
				/*******************************************************************************************/
											//Starting Analyse Syntaxique   ###ECRIRE###
				/*******************************************************************************************/
int Analyse_Syn_ecrire(Element * localFile){
	char c, tab[10]="ecrire";

	if(strcmp(localFile->data,tab)==0){
		
		localFile=defiler(localFile);  // Defiler ecrire
		
		if(localFile!=NULL){	
			if(*localFile->data=='('){
				localFile=defiler(localFile);   		 // Defiler (
						
						if(localFile!=NULL){	
							if( *localFile->data=='"'){		//Traitement ecrire ( " a " ) ;
								localFile = defiler(localFile);	//defiler "
								
								if(localFile!=NULL){
									if(	(*localFile->data>=97)	&&	(*localFile->data<=122) || *localFile->data==' ' ){	// Le cas ou ecrire ( " " ) ;
										localFile = defiler(localFile);	//defiler variable or white space
									
										if(localFile!=NULL){
											if(*localFile->data == '"'){
												localFile = defiler(localFile);	// defiler "
												
												if(localFile!=NULL){
													if(*localFile->data==')'){
														localFile =defiler(localFile);
														
														if(localFile!=NULL){
															if(*localFile->data==';'){
																localFile = defiler(localFile);   // defiler 
																
																return 1;		//Alhamdulilah SYN Successful
																
															}else{
																return 3; 		//manque d'un ;
															}
														}else{
															return 3; 		//manque d'un ;
														}
																		    															
													}else{
														return 0;			//manque d'un  )
													}
											}else{
												return 0; 	//manque de )
											}
										}else{
											return 6;		//manque d' un "
										}
										
								}else {
									return 6;	//manque d' un "
								}
								}else{
									return 4;		//Manque d'un var
								}
									
							}else{
								return 4 ; // manque des guillemets "
							}
							//****************************************
								// Traitement de ecrire ( x ) ;
							//****************************************
									
					}else if((	(*localFile->data>=97)	&&	(*localFile->data<=122) ) ){		// dans le cas ou 
						localFile = defiler(localFile);	//defiler variable or white space
						
						if(localFile!=NULL){
							if(*localFile->data==')'){
								localFile = defiler(localFile);
								
								if(localFile!=NULL){
									if(*localFile->data==';'){
										localFile = defiler(localFile);
										
										return 1;		//Alhamdulilah SYN Successful
										
									}else{
										return 3; 	//manque d'un ;
									}
								}else{
										return 3; 	//manque d'un ;
								}
							}else{
								return 2; 		    //manque d'une )
							}
						}else{
							return 2;  				//manque d'une )
						}
					
					}else {
						return 8; 					//manque d'une valeur
					}
					
					
				
				}else{
					return 6; 			// lorsqu'il manque d'une "  
			
				}
	
			}else{
					return 2;			//manque d'une parenthese ouvrante
			}
		}else{
			return 2;			//manque d'une parenthese ouvrante
		}
		
	}else{
		return -1;
	}
}
	
				/*******************************************************************************************/
											//Starting Analyse Syntaxique   ###SI###
				/*******************************************************************************************/		

int Analyse_Syn_Si(Element *localFile){
	//	afficher(localFile);
		char tab[10]="si";
		int checkInnerSi =0;
		if(strcmp(localFile->data,tab)==0){
			localFile = defiler(localFile);   // Defiler si
				if(localFile!=NULL){
					
					if(*localFile->data=='('){
						localFile = defiler(localFile); 	 // Defiler (
						if(localFile!=NULL){
													    
							if(	(*localFile->data>=97)	&&	(*localFile->data<=97+25) ){ 
								localFile = defiler(localFile);   //Defiler a		
								if(localFile!=NULL){
									
									if(*localFile->data== '>'||  *localFile->data=='/'|| *localFile->data=='<' || *localFile->data=='='){
										localFile = defiler(localFile);   //Defiler l'operateur
										if(localFile!=NULL){
											
											if((*localFile->data>=97)	&&	(*localFile->data<=97+25)){
												localFile = defiler(localFile);		//Defiler l'operateur b
												if(localFile!=NULL){
													
													if(*localFile->data==')'){
													localFile = defiler(localFile);	//Defiler  )
														if(localFile!=NULL){
															if(strcmp(localFile->data,"alors")==0){
																localFile = defiler(localFile);
																while(strcmp(localFile->data,"finsi")!=0&& localFile->data[0]!=';'&&localFile!=NULL){
																	//ICI JE DOIS REFAIRE LE TESTE DE TOUT LES FCT LIRE ECERIE ...
																	localFile = defiler(localFile);
																	
																}
		
																if(localFile!=NULL){
																	if(strcmp(localFile->data,"finsi")==0){
																	localFile = defiler(localFile);
																		if(localFile!=NULL){
																			if(localFile->data[0]==';'){
																				localFile = defiler(localFile);
																				
																				return 1;
																			}else{
																				return 3;// manque d'un ;
																			}
																		}else{
																			return 3; // MANQUE d'un ;
																		}
																	}else{
																	return 11;		//manque de finsi
																	}
																}else{
																	return 11;	//manque de finsi
																}					
															}else {
																return 10; //manque de alors   
															}			
														}else{
															return 10;			//manque de alors
														}
													}else{
														return 2; 				//Manque d'un )
													}
												}else{
													return 2;					//Manque d'un )
												}
											}else{
												return 4; // manque d'un variable  b
											}
										}else{
											return 4; //manque d'un variable   b
										}
									
									}else{
										return 5;		//manque d'un operateur
									}	
								}else{
									return 5; 		//manque d'un operateur
								}
								
							}else{
								return 4; 	// manque d'un variable
							}
						}else{
							return 4 ; 		//manque d'un variable;
						}
					}else{
						return 0;  // Manque d'une parenthese ouvrante
					}
				}else{
					return 0;  // Manque d'une parenthese ouvrante
				}	
		}else{
			return -1;
		}
}
				/*******************************************************************************************/
											//Starting Analyse Syntaxique   ###VARIABLE###
				/*******************************************************************************************/
int Analyse_Syn_variable(Element * localFile){	
	char tab[10]="variable";
	if(strcmp(tab,localFile->data)==0){
		localFile = defiler(localFile);	// defiler variable 
		
		if(localFile!=NULL){
			if(	(*localFile->data >=97) && (*localFile->data <=122)	&& localFile->data[1]=='\0'){
				localFile = defiler(localFile); 	//defiler caractere
				
				if(localFile!=NULL){
					if(strcmp(localFile->data,"entier")==0 || strcmp(localFile->data,"reel")==0 ||strcmp(localFile->data,"caractere")==0){
						localFile =defiler(localFile);
						
						if(localFile!=NULL){
							if(*localFile->data==';'){
								localFile = defiler(localFile);
								
								return 1 ; 		//mission succes
							}else{
								return 3;	// manque d'un ;
							}
						}else{
							return 3;	// manque d'un ;
						}
						
					}else{
						return 7;	// manque d'un type
					}
				}else{
					return 7; // manque d'un type	
				}
			}else{
				return 4; 	// manque d'un VARIABLE
			}
		}else{
			return 4; 	//manque d'un variable
		}
			
	}else{
			return -1; 	//le cas strcmp(tab,localFile->data)!=0
	}
}


							//****************************************
								// ANALYSE SYN DE L'AFFECTATION
							//****************************************
int verifierLaffectation(Element *localFile){

		
	if(localFile!=NULL){
		if(localFile->data[0]>=97 && localFile->data[0]<=122){		// defiler le var
			localFile = defiler(localFile);
			
			if(localFile!=NULL){
				if(localFile->data[0]=':'&&localFile->data[1]=='='){		
					localFile = defiler(localFile);		// defiler le := de l'affectation	
					
						if(localFile!=NULL){		
							if(localFile->data[0]!=';'){					
								localFile = defiler(localFile);		//defiler  la valeur de l'affectation peut etre'a' ou 1 ...
							
								if(localFile!=NULL){
									if(localFile->data[0]==';'){
										//printf("\naffectation succeded");
										localFile = defiler(localFile);
										return 1;
									}else{
										return 3;
									}
								}else{
									return 3;
								}
							}else{
								return 9;	//manque d'une val
							}													
						}else{
							return 9; 	//manque d'une val de var
						}		
				}
			}
		}
	}
return 0;	
}					
						
			

#include <stdio.h>
#include <stdlib.h>
struct ElementChar {
 char nom;			//je vais stocké ici les noms des variales de types Char
 char valeur;		//ici leur valeurs
 struct ElementChar * next;
};
typedef struct ElementChar ElementChar;
// struct Pile

void afficherChar(ElementChar * T){
    ElementChar *tmp= T;
    if(T==NULL) {
        printf("\n+la Pile est vide");
        exit(1);
    }
    while(tmp!=NULL){
        printf("\n |nom %c valeur %c|  ", tmp->nom, tmp->valeur);
        tmp = tmp->next;
    }

}

ElementChar * emfilerChar(ElementChar * T, char nom ){

    ElementChar *nv = (ElementChar *)malloc(sizeof(ElementChar)), *tmp = T;
    nv->nom = nom;
    nv->next = NULL;
    if(T==NULL){
        T = nv;
        return T;
    }

    while(tmp->next!= NULL){
        tmp = tmp->next;
    }
    tmp->next = nv;

    return T;
}

ElementChar* defilerChar(ElementChar *T){
ElementChar *tmp = T;
//printf("\n l'ElementChar %s est defiler ",T->nom);
if(T==NULL){
	printf(" \n La file est vide\n ");
}
T= T->next;
free(tmp);
return T;
}


//int main()
//{   ElementChar *CharFile=NULL; // inisialisation est importante
//    CharFile = emfilerChar(CharFile,'a','z');
//    CharFile = emfilerChar(CharFile,'a','z');
//    CharFile = emfilerChar(CharFile,'a','z');
//    if(CheckIfNameOfVarExisted(CharFile, 'a')){
//        printf("v existed");
//    }else{
//        printf("v not existed");
//    }
//    afficherChar(CharFile);
//    printf("Hello world!\n");
//    return 0;
//}


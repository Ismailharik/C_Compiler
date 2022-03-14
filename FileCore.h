struct Element {
 char data[10];		//dans le cas list des entier je vais mettre ici nom du var 
 int ligne;			// et ici comme val des entier
 struct Element * next;
};
typedef struct Element Element;
// struct 

Element * emFiler(Element * T,int ligne, char *x){

    Element *nv = (Element *)malloc(sizeof(Element)), *tmp = T;
    strcpy(nv->data, x);
    nv->ligne = ligne;
    nv->next = NULL;
    if(T==NULL){
       // printf("empty");
        T = nv;
        return T;
    }

    while(tmp->next!= NULL){
        tmp = tmp->next;
    }
    tmp->next = nv;
    
    return T;
}
void afficher(Element * T){
    Element *tmp=T;
    if(tmp==NULL) {
        printf("\n+la Pile est vide");
        exit(1);
    }
    while(tmp!=NULL){
        printf("\n |%s|  %d", tmp->data,tmp->ligne);
        tmp = tmp->next;
    }

}
Element* defiler(Element *T){
Element *tmp = T;
//printf("\n l'element %s est defiler ",T->data);
if(T==NULL){
	printf(" \n La file est vide\n ");
}
T= T->next;
free(tmp);
return T;
}


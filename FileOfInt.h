typedef struct Element Element;
// struct Pile
struct ElementInt{
char nom;		//je vais stocké ici les noms des variales de types entiers
int valeur;		//ici leur valeurs
struct ElementInt *next;
};
typedef struct ElementInt ElementInt;
ElementInt * emFilerInt(ElementInt * T, char x){

    ElementInt *nv = (ElementInt *)malloc(sizeof(ElementInt)), *tmp = T;
    nv->nom= x;
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







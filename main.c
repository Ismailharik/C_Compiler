#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "FileCore.h"
#include "FileOfChar.h"
#include "FileOfInt.h"
Element *ProgList=NULL;
Element *DictList=NULL;
ElementInt *ListOfEntier = NULL;
ElementChar *ListOfCharactere = NULL;
#include "AnalyseSyn.h"
#include "AnalyseSem.h"
#include "AnalyseLix.h"
#include "Interpretation.h"

int main(int *Ligne, char **argv ){
	
	if(	analyser_lix()){
		printf("\n ANALYSE LIX-SYN-SEM SUCCES");
		interpretation(ProgList);
	}else{
	printf("\n CORRIGER VOS ERROR ON PEUT PAS PASSER A L'INTERPRETATION'");
	}
	
	printf("\n***********FIN***************");
///afficher(ProgList);
return 0;
}



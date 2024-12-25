#include <malloc.h>

struct noeud{
    int elt;
    struct noeud *G;
    struct noeud *D;
};

typedef struct noeud noeud_t;


noeud_t* instancier(int don, noeud_t* gauche, noeud_t* droite){
    noeud_t *nouveau;
    if(nouveau=(noeud_t*) malloc(sizeof(noeud_t))){
        nouveau->elt=don;
        nouveau->D=droite;
        nouveau->G=gauche;
    }
    return nouveau;
}

void Inserer_ARB(noeud_t* R, int don){
    
    if(!R){
        R = instancier(don,NULL,NULL);
    }else if(don<=R->elt){
        Inserer_ARB(R->G,don);
    }else{
        Inserer_ARB(R->D,don);
    }



}



int NbN(noeud_t* R){
    if(!R) return 0;
    else return 1+NbN(R->D)+NbN(R->G);
}

int estFeuille(noeud_t *N){
    return !(N->G || N->D);
}

int NbF(noeud_t* R){
    if(!R) return 0;
    else if(estFeuille(R)) return 1;
    else return NbF(R->D)+NbF(R->G);

}

int recherche(int don,noeud_t* R){
    if(!R) return 0;
    else if(don == R->elt) return 1;
    else if(don < R->elt) return recherche(don,R->G);
    else return recherche(don,R->D);
}

void supprimer(int X, noeud_t **R)
{
 noeud_t * p;
 if (*R){ 
    if (X<(*R)->elt)
        supprimer(X,&((*R)->G));
    else if (X>(*R)->elt)
        supprimer(X,&((*R)->D));
    else{
        if ((*R)->G == NULL){ 
            p=*R; 
            *R = (*R)->D; 
            free((char*)p);
        }
        else if ((*R)->D == NULL){ 
            p=*R; 
            *R = (*R)->G; 
            free((char*)p);
        }
        else Remplacer(&((*R)->G),R);
        } 
    }
}
void Remplacer(noeud_t **R1, noeud_t **R)
{
 noeud_t *p;
 if ((*R1)->D != NULL)
    Remplacer(&((*R1)->D),R);
 else { 
    (*R)->elt = (*R1)->elt;
    p = *R1;
    *R1 = (*R1)->G; //car *R1 = R1->D
    free((char *)p);
    } 
} 

    








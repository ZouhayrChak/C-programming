#include <stdio.h>
#include <malloc.h>


struct noeud{

    float coeff;
    unsigned puiss;
    struct noeud *suiv;

};

typedef struct noeud noeud_t;
noeud_t** creer();
void lire_poly(noeud_t**);
noeud_t* instancier(int );
void inserer(noeud_t*, noeud_t**);
void normaliser(noeud_t **);
void afficher(noeud_t** );
void derivee(noeud_t** );
void primitive(noeud_t** );
//liste double




int main(){

    noeud_t** poly=creer();
    
    int choix;

    do{
        printf("--------------- Menu --------------------\n");
        printf("1. entrer le polynome \n");
        printf("2. Normaliser le polynome \n");
        printf("3. afficher \n");
        printf("4. derivee \n");
        printf("5. primitive\n");
        printf("6. Quitter \n");

        printf("Entrez votre choix: ");
        scanf("%i",&choix);

        switch (choix)
        {
            case 1:
                lire_poly(poly);
                break;
            case 2:
                normaliser(poly);
                break;
            case 3:
                afficher(poly);
                break;
            case 4:
                derivee(poly);
                break;
            case 5:
                primitive(poly);
                break;
            case 6:
                printf("Au revoir !!");
                break;

        }
        
    }while(choix!=6);

    



    
           
    return 0;
}


noeud_t** creer(){
    noeud_t** poly = (noeud_t**)malloc(sizeof(noeud_t*));
    *poly=NULL;
    return poly;
}


void lire_poly(noeud_t** poly){


        int degre;
        printf("Entrez le dgré du polynome: ");
        scanf("%i",&degre);

        int puiss=degre;

        while(puiss>=0){
             noeud_t* monome=instancier(puiss);
             
             inserer(monome,poly);

            puiss--;

        }   

}

            




noeud_t* instancier(int puiss){
    noeud_t* monome=NULL;

    if(monome=(noeud_t*) malloc(sizeof(noeud_t))){

            
            printf("Entrez le coefficient du monome N° %i: ",puiss);
            scanf("%f",&monome->coeff);
            
            monome->puiss=puiss;
           
            monome->suiv=NULL;

     }
     return monome;
}



void inserer(noeud_t* monome, noeud_t** poly){
    
    if(!(*poly)){
        (*poly)=monome;
        
    }
    else{
        noeud_t* p=(*poly);
        
        while(p->suiv){
            p=p->suiv;
        }
        p->suiv=monome;
        

    }
    
}



void normaliser(noeud_t** poly){

     if((*poly)){

        float coeff_norm=(*poly)->coeff;
        noeud_t* p=(*poly);
        while(p){
            p->coeff=p->coeff/coeff_norm;
            p=p->suiv;
        }
    }

}


void afficher(noeud_t** poly){

        
        printf("P(X)= ");

        noeud_t* p=(*poly);
        while(p){
            if(p->coeff){
                if(p->puiss==0){
                    printf("%.2f",p->coeff);
                }else if(p->puiss==1){
                    printf("%.2fX",p->coeff);
                }
                else{
                    printf("%.2fX^(%i)",p->coeff,p->puiss);
                }

            }
            if(p->suiv && (p->suiv)->coeff!=0)
                printf("+");
            p=p->suiv;
        }
        printf("\n");

    


}

void derivee(noeud_t** poly){

    if(*poly){
        
        noeud_t* p=*poly;

        while(p){
            if(p->puiss>0){
                p->coeff=p->coeff*p->puiss;
                p->puiss--;
                
            }else{
                p->coeff=0;
            }
            p=p->suiv;
        }
        
        
    }

}
    
void primitive(noeud_t** poly){

    if(*poly){
        noeud_t* p=*poly;
        while(p){
            p->coeff=p->coeff/(p->puiss+1);
            p->puiss++;
            p=p->suiv;

        }


    }



}









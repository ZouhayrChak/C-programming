#include <stdio.h>
#include <malloc.h>
#define MAX 100

typedef struct {
    char t[MAX];
    int sommet;
} pile;

void initPile(pile* p);
int estVide(pile p);
int estPleine(pile p);
int empiler(char c, pile* p);
char depiler(pile* p);


int main(){

    

    
    return 0;
}   

//Pile

void initPile(pile* p){
    p->sommet=-1;    
}

int estVide(pile p){
    return (p.sommet == -1);
}

int estPleine(pile p){
    return (p.sommet == MAX-1); 
}

int empiler(char c,pile* p){
    if(!estPleine(*p)){
        p->t[++p->sommet]=c;
        return 1; 
    }
    return 0;
}
char depiler(pile* p){
    if(!estVide(*p))
        return p->t[p->sommet--]; 
    return '\0';
}

// Expression postfixee
int estOperateur(char c){
    return (c=='+' || c=='-' || c=='*' || c=='/'); 

}
pile* consp(char EA[],int len){

    pile* p=(pile*) malloc(sizeof(pile));
    
    for(int i=0;i<len;i++){
        if(EA[i] != '(' && !estOperateur(EA[i]) && EA[i] != ")"){
            empiler(EA[i],p);   
        }
    }

    




}



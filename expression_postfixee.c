#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
void consp(int* i, char expr[], pile* p);
int eval(pile* p);

int main() {
    pile* p = (pile*)malloc(sizeof(pile));
    initPile(p);

    char expr[] = "((2+3)*4)"; 
    
    int index=0;
    
    consp(&index, expr, p);

    printf("Postfixée : ");
    for (int i = 0; i <= p->sommet; i++) {
        printf("%c", p->t[i]);
    }
    printf("\n");

    
    int resultat = eval(p);
    printf("Résultat : %d\n", resultat);

    free(p);
    return 0;
}


void initPile(pile* p) {
    p->sommet = -1;
}

int estVide(pile p) {
    return p.sommet == -1;
}

int estPleine(pile p) {
    return p.sommet == MAX - 1;
}

int empiler(char c, pile* p) {
    if (!estPleine(*p)) {
        p->t[++(p->sommet)] = c;
        return 1;
    }
    return 0;
}

char depiler(pile* p) {
    if (!estVide(*p)) {
        return p->t[(p->sommet)--];
    }
    return '\0';
}


int estOperateur(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}


void consp(int* i, char expr[], pile* p) {
    if (expr[*i] == '(') {
        (*i)++;
        consp(i, expr, p); 
        (*i)++;
        char oper = expr[*i];
        (*i)++;
        consp(i, expr, p); 
        (*i)++;
        empiler(oper, p);  
    } else { 
        empiler(expr[*i], p); 
    }
}



int eval(pile* p) {
    pile* temp = (pile*)malloc(sizeof(pile));
    initPile(temp);

    for (int i = 0; i <= p->sommet; i++) {
        char c = p->t[i];

        if (isdigit(c)) { 
            empiler(c - '0', temp); 
        } else if (estOperateur(c)) { 
            int b = depiler(temp);
            int a = depiler(temp);

            int res = 0;
            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            empiler(res, temp);
        }
    }

    int resultat = depiler(temp);
    free(temp);
    return resultat;
}

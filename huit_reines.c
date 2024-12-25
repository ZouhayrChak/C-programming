#include <stdio.h>

void reines(int t[][8], int);
void set2(int t[][8], int , int);
void initialiser(int t[][8]);
void reset2(int t[][8]);
int main(){

    int t[8][8];
    initialiser(t);

   
    reines(t,0);
    return 0;
}

void initialiser(int t[][8]){

     for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            t[i][j]=0;
        }
    }

}


void reines(int t[][8],int ligne){
    if(ligne==8){
        printf("--------- Solution trouvee--------\n");
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                   printf("%i ",t[i][j]);
                }
                printf("\n");
             }
        

    }else{
        for(int i=0;i<8;i++){
            if(t[ligne][i]!=2){
                t[ligne][i]=1;
                set2(t,ligne,i);
                reines(t,ligne+1);
                t[ligne][i] = 0;
                reset2(t);
                
            }



        }
    }

}


void set2(int t[][8],int ligne, int col){
    for(int j=0; j<8;j++){
        if(j!=col)
            t[ligne][j]=2;
    }

    for(int i=0; i<8;i++){
        if(i!=ligne)
            t[i][col]=2;
    }

    int i=ligne+1;
    int j=col+1;
    while(i<8 && j<8){
        t[i][j]=2;
        i++;
        j++;
    }
    int p=ligne-1;
    int q=col-1;
    while(p>=0 && q>=0){
        t[p][q]=2;
        p--;
        q--;
    }

    int k=ligne+1;
    int m=col-1;
    while(k<8 && 0<=m){
        t[k][m]=2;
        k++;
        m--;
    }

    int l=ligne-1;
    int n=col+1;
    while(l>=0 && n<8){
        t[l][n]=2;
        l--;
        n++;
    }





}

void reset2(int t[][8]) {
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (t[i][j] == 2) {
                t[i][j] = 0;
            }
        }
    }

    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (t[i][j] == 1) {
                set2(t, i, j);
            }
        }
    }
}

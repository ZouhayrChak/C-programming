#include <stdio.h>
#include <string.h>

void remplissage(FILE* f);
void affichage(FILE* f);
void ajout(FILE* f);
void suppression(FILE* f);
void modification(FILE* f);
int existe(int Mat, char []);
void Recherche(FILE* f);
void tri_OM(FILE* f);
void tri_OA(FILE* f);
void move(char NFichier[]);



typedef struct{

    int J;
    int M;
    int A;

} date;

typedef struct{

    int Mat;
    char NP[30];
    float moyenne;
    date DN;

} Etudiant;

int main(){

    FILE* f;
    
    int choix;

    do{
    
    printf("------------- Menu ----------------\n");
    printf("1. remplissage \n");
    printf("2. affichage \n");
    printf("3. recherche \n");
    printf("4. tri/Moyenne \n");
    printf("5. tri/NP \n");
    printf("6. ajout \n");
    printf("7. suppression \n");
    printf("8. modification \n");
    printf("9. Quitter \n");

    printf("Entrez votre choix: ");
    scanf("%i",&choix);        
    getchar();
    switch(choix){
        case 1: 
            remplissage(f);
            break;
        case 2:
            affichage(f);
            break;
        case 3:
            Recherche(f);
            break;
        case 4:
            tri_OM(f);
            break;
        case 5:
            tri_OA(f);
            break;
        case 6:
            ajout(f);
            break;
        case 7:
            suppression(f);
            break;
        case 8:
            modification(f);
            break;
        case 9:
            printf("Au revoir!!!");
            break;
    }

    } while (choix!=9);
    

    remove("temp.txt");

    return 0;
}





void remplissage(FILE* f){

    int nb_etudiants;
    printf("Entrez le nombre d'étudiants: ");
    scanf("%d",&nb_etudiants);
    getchar();

    Etudiant etudiant;


    char NFichier[30];
    printf("Entrez le nom du fichier où stocker les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"w");
    int C=1;
    while(C<=nb_etudiants){
        printf("----------- informations de l'etudiant %d-------------\n",C);

        printf("Entrez le matricule de l'etudiant: ");
        scanf("%i",&etudiant.Mat);
        getchar();

        if(existe(etudiant.Mat,NFichier)){
            printf("le matricule existe déjà");
            continue;
        }    

        printf("Entrez le nom et prenom de l'etudiant: ");
        gets(etudiant.NP);
        

        printf("Entrez la moyenne de l'etudiant: ");
        scanf("%f",&etudiant.moyenne);
        

        printf("Entrez la date de naissance de l'etudiant sous la forme JJ/Mois/Annee: ");
        scanf("%d/%d/%d",&etudiant.DN.J,&etudiant.DN.M,&etudiant.DN.A);
        

        fwrite(&etudiant,sizeof(Etudiant),1,f);
        C++;
    }
    fclose(f);
    
}

void affichage(FILE* f){

    char NFichier[30];
    printf("\nEntrez le nom du fichier dont vous voulez afficher le contenu: ");
    gets(NFichier);


    f=fopen(NFichier,"r");

    Etudiant etudiant;
    
    printf("  Mat................NP...............moyenne..............DN \n ");

    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        
        printf(" %d        %s          %f         %d/%d/%d \n",etudiant.Mat,etudiant.NP,etudiant.moyenne,etudiant.DN.J,etudiant.DN.M,etudiant.DN.A);

    }    
    fclose(f);

}

void ajout(FILE* f){


    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"a");

    Etudiant etudiant;

    printf("Entrez le matricule de l'etudiant: ");
    scanf("%i",&etudiant.Mat);
    getchar();

    if(!existe(etudiant.Mat,NFichier)){
        printf("Entrez le nom et prenom de l'etudiant: ");
        gets(etudiant.NP);
        

        printf("Entrez la moyenne de l'etudiant: ");
        scanf("%f",&etudiant.moyenne);
        

        printf("Entrez la date de naissance de l'etudiant sous la forme JJ/Mois/Annee: ");
        scanf("%d/%d/%d",&etudiant.DN.J,&etudiant.DN.M,&etudiant.DN.A);
        getchar();

        fwrite(&etudiant,sizeof(Etudiant),1,f);

            
        }else{
            printf("le matricule existe déjà");    
        }  

    

    fclose(f);

}

void suppression(FILE* f){

    int Mat;
    
   
    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"r");
    Etudiant etudiant;


    FILE* FP;
    FP=fopen("temp.txt","w");

    printf("Entrez le matricule de l'etudiant à supprimer: ");
    scanf("%i",&Mat);
    getchar();
    
    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        if(etudiant.Mat!=Mat)
            fwrite(&etudiant,sizeof(Etudiant),1,FP);
    }
    fclose(FP);
    fclose(f);

    move(NFichier);
    

    
}

void modification(FILE* f){

    int Mat;
    
   
    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"r");
    

    FILE* FP;
    
    FP=fopen("temp.txt","w");

    printf("Entrez le matricule de l'etudiant dont vous voulez modifier les informations: ");
    scanf("%i",&Mat);
    getchar();

    Etudiant nouveau_etudiant;
    
    if(existe(Mat,NFichier)){
    
        printf("Entrez le nom et prenom de l'etudiant: ");
        gets(nouveau_etudiant.NP);
            

        printf("Entrez la moyenne de l'etudiant: ");
        scanf("%f",&nouveau_etudiant.moyenne);
            

        printf("Entrez la date de naissance de l'etudiant sous la forme JJ/Mois/Annee: ");
        scanf("%d/%d/%d",&nouveau_etudiant.DN.J,&nouveau_etudiant.DN.M,&nouveau_etudiant.DN.A);
        getchar();
        nouveau_etudiant.Mat=Mat;
    }
    Etudiant etudiant;
    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        if(etudiant.Mat!=Mat)
            fwrite(&etudiant,sizeof(Etudiant),1,FP);
        else 
            fwrite(&nouveau_etudiant,sizeof(Etudiant),1,FP);   
    }
    fclose(FP);
    fclose(f);

    move(NFichier);
    

}


int existe(int Mat, char NFichier[20]){

    FILE* f;

    f=fopen(NFichier,"r");

    
    Etudiant etudiant;
    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        if(etudiant.Mat==Mat)
            return 1;
    }
    return 0;

    fclose(f); 

}

void Recherche(FILE* f){

    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"r");
    
    int Mat;
    printf("Entrez le matricule de l'etudiant dont vous voulez obtenir les informations: ");
    scanf("%i",&Mat);
    getchar();

    Etudiant etudiant;
    if(existe(Mat,NFichier)){
        while(fread(&etudiant,sizeof(Etudiant),1,f))
            if(etudiant.Mat==Mat){
                printf(" %d        %s          %f         %d/%d/%d \n",etudiant.Mat,etudiant.NP,etudiant.moyenne,etudiant.DN.J,etudiant.DN.M,etudiant.DN.A);
            }
    }else{
        printf("l'etudiant n'existe pas");
    }

    fclose(f);


}


void tri_OM(FILE* f){

   
    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"r");

    FILE* FP=fopen("temp.txt","w");

    Etudiant etudiants[100];

    int i=0;

    Etudiant etudiant;
    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        etudiants[i]=etudiant; 
        i++;  
    }  

    int len = i;
    
    int permuter=1;
    Etudiant temp;
    while(permuter){
        permuter=0;
        for(int i=0;i<len-1;i++){
            if(etudiants[i].moyenne <= etudiants[i+1].moyenne){
                temp=etudiants[i];
                etudiants[i]=etudiants[i+1];
                etudiants[i+1]=temp;
            }

        }
    }

    for(int i=0;i<len;i++){
        fwrite(&etudiants[i],sizeof(Etudiant),1,FP);
    }




    
    fclose(f);
    fclose(FP);

    move(NFichier);
    
}


void move(char NFichier[]){

    FILE* f=fopen(NFichier,"w");

    FILE* fp=fopen("temp.txt","r");

    Etudiant etudiant;
    while(fread(&etudiant,sizeof(Etudiant),1,fp)){
        fwrite(&etudiant,sizeof(Etudiant),1,f);
    }


    fclose(f);
    fclose(fp);

}


void tri_OA(FILE* f){

    char NFichier[30];
    printf("Entrez le nom du fichier où sont stockees les informations: ");
    gets(NFichier);

    f=fopen(NFichier,"r");

    FILE* FP=fopen("temp.txt","w");

    Etudiant etudiants[100];

    int i=0;

    Etudiant etudiant;
    while(fread(&etudiant,sizeof(Etudiant),1,f)){
        etudiants[i]=etudiant; 
        i++;  
    }  

    int len = i;
    
    int permuter=1;
    Etudiant temp;
    while(permuter){
        permuter=0;
        for(int i=0;i<len-1;i++){
            if(strcmp(etudiants[i].NP,etudiants[i+1].NP)>=0){
                temp=etudiants[i];
                etudiants[i]=etudiants[i+1];
                etudiants[i+1]=temp;
            }

        }
    }

    for(int i=0;i<len;i++){
        fwrite(&etudiants[i],sizeof(Etudiant),1,FP);
    }




    
    fclose(f);
    fclose(FP);

    move(NFichier);
    
}









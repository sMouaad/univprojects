#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
void sortir();
void menunotes();
void variancemode(float *ptr, int*taille, float *x);
void medianenotes(float* pinteur, int*taille,char tn);
void menu();
void histogrammme(float* pointeur, int *taille);
int countlines(char* filenom);
int main() {
    int i,taille;
    bool abandon = false;
    float adm=0,*ptr,max=0,min=20,s=0;
    char filename[50],ext=' ',choice,input,choicenote;
    FILE* 	fichier;
    while(choice!='0') {
        printf("\e[1;1H\e[2J"); // Alternative à system clear pour éviter le problème d'incompatiblité (OS)
        menu();
        scanf(" %c", &choice);
        switch(choice){
        case '1' :
            printf("\e[1;1H\e[2J");
            printf("\nEntrez le nom du fichier : ");
            scanf(" %s", filename);
            printf("\e[1;1H\e[2J");
            printf("Choisissez l'extension du fichier :\n1: Fichier texte (.txt)\n2: Fichier Excel Classeur (.csv)\n\n\nVotre choix : ");
            scanf(" %c", &ext);
            while (ext!='1' && ext!='2') {
                printf("\e[1;1H\e[2J");
                printf("1: Fichier texte (.txt)\n2: Fichier Excel Classeur (.csv)\n\n\nEntrez 1 ou 2 : ");
                scanf(" %c", &ext);
            }
            if(ext=='1') {
                strcat(filename,".txt"); //ajouter l'extension sans qu'il fasse l'utilisateur
            }
            else if (ext=='2') {
                strcat(filename,".csv");
            }
            fichier = fopen(filename, "r");
	        if (fichier != NULL){
                printf("\e[1;1H\e[2J");
                printf("\nVoulez vous enlever les zeros ?\n1 : Oui\n2 : Non\n\n\n?:  "); //abandon
                scanf(" %c", &ext);
                while (ext!='1' && ext!='2') {
                    printf("\e[1;1H\e[2J");
                    printf("Choix erronee...\nVoulez vous enlever les zeros ?\n1 : Oui\n2 : Non\n\n\n?:  ");
                    scanf(" %c", &ext);
                }
                if(ext=='1') {
                    abandon=true;
                }
                taille = countlines(filename); //compte combien de lignes
                ptr = (float*)malloc(sizeof(float)*taille);
                i=0;
                while( !feof(fichier) ) {
                fscanf(fichier,"%f", &ptr[i]);
                if(abandon==true) {
                    if (ptr[i]==0) {
                        i--;
                    }
                }
                else {
                    if(ptr[i]>max) {
                        max = ptr[i]; //calcul de max
                    }
                    if(ptr[i]<min){
                    min = ptr[i]; //calcul de min
                    }
                    if(ptr[i]>=10) {
                    adm++;
                    }
                }
                i++;
                }
            if(abandon==true){
                taille = i;
                ptr = realloc(ptr,taille*sizeof(float));
            }
            for ( i=0 ; i<taille ; ++i ){
        	    s+=ptr[i];                      //Calcul Moyenne
            }
            s=s/taille;
            fclose(fichier);
    	    }
            else {
                printf("\e[1;1H\e[2J");
                printf("Impossible d'ouvrir le fichier, verifiez l'extension ou le nom du fichier.  \n \n");
            }
            sortir();
            break;
        case '2':
            printf("\e[1;1H\e[2J");
            if(fichier!=NULL) {
                printf(" ____________________Statistiques____________________\n\n"); 
                printf("La moyenne : %.2f\n\nLe max : %.2f\n\nLe min : %.2f\n\n", s, max, min);
                medianenotes(ptr,&taille,'4');
                variancemode(ptr,&taille,&s);
                printf("Taux d'admis : %.2f%c\n\n", ((adm/taille)*100),'%');
                printf("L'etendue : %.2f\n____________________________________________________",(max-min));
            }
            else {
                printf("Il faut d'abord lire un fichier\n");
            }
            sortir();
            break;
        case '3' :
            printf("\e[1;1H\e[2J");
            if(fichier!=NULL) {
            histogrammme(ptr,&taille);
            }
            else {
                printf("Il faut d'abord lire un fichier!\n");
            }
            sortir();
            break;
        case '4' :
            choicenote=' ';
            printf("\e[1;1H\e[2J"); //afficher les notes
            if(fichier!=NULL) {
                printf("\e[1;1H\e[2J");
                menunotes();
                scanf(" %c", &choicenote);
                switch(choicenote) {
                    case '1' :
                        printf("\e[1;1H\e[2J");
                        medianenotes(ptr,&taille,'1');
                        sortir();
                        printf("\e[1;1H\e[2J");
                        break;
                    case '2' :
                        printf("\e[1;1H\e[2J");
                        medianenotes(ptr,&taille,'2');
                        sortir();
                        printf("\e[1;1H\e[2J");
                        break;
                    case '3' :
                        printf("\e[1;1H\e[2J");
                        medianenotes(ptr,&taille,'3');
                        sortir();
                        printf("\e[1;1H\e[2J");
                        break;
                    default :
                        printf("\e[1;1H\e[2J");
                        break;
                    }
            }
            else {
                printf("Il faut d'abord lire un fichier!\n");
            }
            sortir();
            break;
        case '5' :
            printf("\e[1;1H\e[2J");
            printf("____________________Credits____________________\n Mohamed Mouaad Sadi L1 MI SEC 3 2021/2022 LICENSE GPL...\n___________________________");
            sortir();
            break;
        case '0' :
            printf("\e[1;1H\e[2J");
            printf("Merci d'avoir utilisé le logiciel!\n");
            break;
        default:
            printf("\e[1;1H\e[2J");
            printf("ERREUR! Voulez vous recommencer le programme ? Y/N\n");
            scanf(" %c", &input);
            while(input!='y' && input!='Y' && input!='n' && input!='N') {
                printf("\e[1;1H\e[2J");
                printf("\nERREUR! Tapez y pour revenir ou n pour arreter le programme : ");
                scanf(" %c", &input);
            }
            if(!(input=='y' || input == 'Y')) {
                printf("Merci d'avoir utilise le logiciel!\n");
                scanf(" %c", &input);
                choice = '0';
            }
        }
    }
}
int countlines(char* filenom) {
    FILE* file;
    file = fopen(filenom,"r");
    int i=0;
    float counter[500];
        while( !feof(file) ) {
            fscanf(file,"%f",&counter[i]);
            i++;
        }
        fclose(file);
    return i;
}
void histogrammme(float* pointeur, int *taille) {
    int s[10]={0},j=0,modalite=0;
    for(int i = 0;i<(*taille);i++) {
        if (pointeur[i]>=0 && pointeur[i] <2) {
            s[0]+=1;
        }
        else if (pointeur[i]>=2 && pointeur[i] <4) {
            s[1]+=1;
        }
        else if (pointeur[i]>=4 && pointeur[i] <6) {
            s[2]+=1;
        }                                               //incremente sur chaque intervalle
        else if (pointeur[i]>=6 && pointeur[i] <8) {
            s[3]+=1;
        }
        else if (pointeur[i]>=8 && pointeur[i] <10) {
            s[4]+=1;
        }
        else if (pointeur[i]>=10 && pointeur[i] <12) {
            s[5]+=1;
        }
        else if (pointeur[i]>=12 && pointeur[i] <14) {
            s[6]+=1;
        }
        else if (pointeur[i]>=14 && pointeur[i] <16) {
            s[7]+=1;
        }
        else if (pointeur[i]>=16 && pointeur[i] <18) {
            s[8]+=1;
        }
        else if (pointeur[i]>=18 && pointeur[i] <=20) {
            s[9]+=1;
        }
    }
    printf(" ___________________Histogramme____________________ \n| Notes |");
    while(j<20) {
        if (j >8) {
            printf("\n| %d-%d %c ",j,j+2,195);
        }
        else if (j==8){
            printf("\n| %d-%d  %c ",j,j+2,195);                // Quelque code supplémentaire pour l'esthétique du programme
        }
        else {
            printf("\n| %d-%d   %c ",j,j+2,195);
        }
        for(int i = 0; i <s[modalite];i++) { 
            printf("%c", 223);
        }
        j = j + 2;
        modalite++;
    }printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
}
void medianenotes(float* pinteur, int*taille,char tn) {
    int pmin;
    float t,pointeur[(*taille)];
    for(int i = 0; i<(*taille);i++) {
        pointeur[i] = pinteur[i];
    }
    if(tn=='2' || tn =='3' || tn =='4'){
    for(int i = 0;i<(*taille)-1;i++) {
        pmin = i;
        if(tn=='2' || tn=='4'){
            for(int j = i;j<(*taille);j++) {
                if (pointeur[pmin] > pointeur[j]) {             //tri du vecteur par ordre croissant
                    pmin = j;
                }
            }
        }
        else{
            for(int j = i;j<(*taille);j++) {
                if (pointeur[pmin] < pointeur[j]) {             //tri du vecteur par ordre décroissant
                    pmin = j;
                }
            } 
        }
        if (pmin!=i) {
            t = pointeur[i];
            pointeur[i] = pointeur[pmin];
            pointeur[pmin]=t;
        }
    }
    }
    if(tn=='4'){
    if((*taille)%2==0) {
        printf("La mediane : %.2f\n\n", ((pointeur[((*taille)/2)-1]+pointeur[(*taille)/2])/2));
    }
    else {                                          //afficher mediane
        printf("La mediane : %.2f\n\n", (pointeur[(((*taille)-1)/2)-1]));
    }
    }
    else if(tn=='2'||tn=='3'){
        printf("\e[1;1H\e[2J");
        for(int i = 0;i<(*taille);i++){             //afficher les notes en ordre croissant decroissant
            printf("%d) %.2f\n",i+1,pinteur[i]);
        }
    }
    else {
        printf("\e[1;1H\e[2J");
        for(int i = 0;i<(*taille);i++){ //afficher les notes en ordre tels quel sont
        printf("%d) %.2f\n",i+1,pointeur[i]);
    }
    }
}
void variancemode(float *ptr, int*taille, float *x){
    int max,k,somme2[(*taille)];
    float xi,somme=0;
    for(int i = 0;i<(*taille);i++){
        xi = ptr[i];
        xi = xi*xi;                     //calcul variance
        somme+=xi;
        somme2[i]=0;
    }
    for(int i = 0;i<(*taille)-1;i++){
        for(int j = 0;j<(*taille);j++) {
            if(ptr[i]==ptr[j]) {
                somme2[i]++;                //calcul mode
            }
        }
    }
    max = somme2[0];
    for(int i = 1;i<(*taille);i++){
        if (somme2[i]>max) {            //recherche si il y'a d'autres modes
            max = somme2[i];
            k=i;
        }
    }
    printf("Le mode est : %.2f", ptr[k]);
    for(int i = 0;i<(*taille);i++){
        if(somme2[i]==max && ptr[k]!=ptr[i]) {
            k=i;
            printf(" & ");                          //impression mode
            printf("%.2f",ptr[i]);
        }
    }printf("\n\n");
    somme = (somme/(*taille)) - (*x)*(*x);
    printf("La variance : %.2lf\n\n", somme); //impression variance
    printf("L'ecart type : %.2lf\n\n", sqrt(somme)); //impression ecart type
}
void menu() {
    printf(" _______________________________________________________________________________________________\n");
    printf("|                              Bienvenue, veuillez choisir :                                    |\n");
    printf("|                                                                                               |\n");
    printf("|    1 : Lire un fichier.                                                                       |\n");
    printf("|    2 : Afficher les statistiques.                                                             |\n");
    printf("|    3 : Afficher l'histogramme                                                                 |\n");
    printf("|    4 : Afficher les notes                                                                     |\n");
    printf("|    5 : Credits                                                                                |\n");
    printf("|    0 : Fin                                                                                    |\n");
    printf("|                                                                                               |\n");
    printf("|_______________________________________________________________________________________________|\n\nVotre choix : ");
}
void sortir(){
    char input;
    printf("\n\n\nTapez n'importe quoi pour revenir.\n");
    scanf(" %c", &input);
}
void menunotes() {
    printf(" ___________________________________________NOTES_______________________________________________\n");
    printf("|                                                                                               |\n");
    printf("|    1 : Afficher les notes tels qu'elle sont                                                   |\n");
    printf("|    2 : Afficher les notes en ordre croissant                                                  |\n");
    printf("|    3 : Afficher les notes en ordre decroissant                                                |\n");
    printf("|    0 : Revenir au menu                                                                        |\n");
    printf("|_______________________________________________________________________________________________|\n\nVotre choix : ");
}
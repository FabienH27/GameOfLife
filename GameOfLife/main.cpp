#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


//Generation d'un tableau de taille x, y
int **Generate_Tab(int x, int y){
    int **tab;
    tab =(int**)malloc(sizeof(int*)*x);
    for(int i =0;i<x;i++){
        tab[i]=(int*)calloc(y,sizeof(int));
    }
    return tab;
}

//Initialisation du tableau avec des valeurs comprises entre 0 et 1
void Init_Tab(int **tab, int x, int y){
    int i,j;
    for(i =1;i<x-1;i++){
        for(j =1;j<y-1;j++){
            tab[i][j]=rand()%2;
        }
    }
}

//Affichage du tableau
void Affiche_Tab(int **tab,int nb){
    for(int i = 1;i < nb-1;i++){
        for(int j = 1;j < nb-1;j++){
            cout << tab[i][j] << "\t";
        }cout << endl;
    }
}

//Test du nombre de voisins pour une cellule donnée
int Test_NbVoisins(int **tab, int i, int j){
    int nbVoisins = tab[i-1][j-1] + tab[i][j-1] + tab[i+1][j-1] + tab[i-1][j] + tab[i+1][j] + tab[i-1][j+1] + tab[i][j+1] + tab[i+1][j+1];
    return nbVoisins;
}


//Generation du tableau associé au nombre de voisins de chaque case
int **Generate_NbVoisinsTab(int **tab, int x, int y){
    int **tab2;
    tab2 =(int**)malloc(sizeof(int*)*x);
    for(int i =0;i<x;i++){
        tab2[i]=(int*)calloc(y,sizeof(int));
    }

    for(int i = 1; i < x-1; i++){
        for(int j = 0; j < y-1; j++){
            tab2[i][j] = Test_NbVoisins(tab,i,j);
        }
    }
    return tab2;
}

//Conditions de vie ou de mort pour chaque cellule à la prochaine génération
void NextGeneration(int **tab, int **tabVoisins, int x, int y){
    for(int i = 1;i < x-1;i++){
        for(int j = 1; j < y-1;j++){
            if(tabVoisins[i][j] < 2){
                tab[i][j] = 0;
            }
            else if(tabVoisins[i][j] > 3){
                tab[i][j] = 0;
            }
            else if(tab[i][j] == 0 && tabVoisins[i][j] == 3){
                tab[i][j] = 1;
            }
        }
    }
}

//Fonction principale du programme, on effectue nbRepetition le programme en appelant les différentes fonctions
void Jeu(int **tab,int **tabVoisins, int nb,int nbRepetition){

    for(int i = 0; i < nbRepetition;i++){
        tabVoisins = Generate_NbVoisinsTab(tab,nb,nb);

        NextGeneration(tab,tabVoisins,nb,nb);
        cout << "\n" << i+1 << "eme generation : " << endl;
        Affiche_Tab(tab,nb);
    }

}

//Fonction principale du programme
int main()
{
    int nb = 10;//ne pas oublier de mettre taille+2
    int **tab = Generate_Tab(nb,nb);//Tableau 2D principal

    int **tabNbVoisins;//Tableau associé au nombre de voisins

    Init_Tab(tab,nb,nb);//Initialisation du tableau principal
    Affiche_Tab(tab,nb);//Affichage du tablea

    int nbRepetition;
    //Saisie du nombre de générations voulues
    cout << "Saisir le nombre de repetition" << endl;
    cin >> nbRepetition;

    //Appel à la fonction Jeu() dont le but est de gérer la simulation.
    Jeu(tab,tabNbVoisins,nb,nbRepetition);

    return 0;
}

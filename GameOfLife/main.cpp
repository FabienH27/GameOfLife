#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int **Generate_Tab(int x, int y){
    int **tab;
    tab =(int**)malloc(sizeof(int*)*x);
    for(int i =0;i<x;i++){
        tab[i]=(int*)calloc(y,sizeof(int));
    }
    return tab;
}

void Init_Tab(int **tab, int x, int y){
    int i,j;
    for(i =1;i<x-1;i++){
        for(j =1;j<y-1;j++){
            tab[i][j]=0;
        }
    }

    for(i =1;i<x-1;i++){
        for(j =1;j<y-1;j++){
            tab[i][j]=rand()%2;
        }
    }
}

void Affiche_Tab(int **tab,int nb){
    system("cls");
    for(int i = 1;i < nb-1;i++){
        for(int j = 1;j < nb-1;j++){
            cout << tab[i][j] << "\t";
        }cout << endl;
    }

}

int Test_NbVoisins(int **tab, int i, int j){
    int nbVoisins = tab[i-1][j-1] + tab[i][j-1] + tab[i+1][j-1] + tab[i-1][j] + tab[i+1][j] + tab[i-1][j+1] + tab[i][j+1] + tab[i+1][j+1];
    return nbVoisins;
}


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

void Jeu(int **tab,int **tabVoisins, int nb,int nbRepetition){

    for(int i = 0; i < nbRepetition;i++){
        tabVoisins = Generate_NbVoisinsTab(tab,nb,nb);

        NextGeneration(tab,tabVoisins,nb,nb);
        Affiche_Tab(tab,nb);
    }

}

int main()
{
    int nb = 10;//ne pas oublier de mettre taille+2
    int **tab = Generate_Tab(nb,nb);

    int **tabNbVoisins;

    Init_Tab(tab,nb,nb);
    Affiche_Tab(tab,nb);

    int nbRepetition;
    cout << "Saisir le nombre de repetition" << endl;
    cin >> nbRepetition;

    Jeu(tab,tabNbVoisins,nb,nbRepetition);

    return 0;
}

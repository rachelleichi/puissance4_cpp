#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Puissance4.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    int piece = rand() % 2; 
  
      int x;
      cout << " veillez entrer le niveau max du jeux :" << endl;
      cin >> x;
      Puissance4 jeu(x);
      jeu.affichage();
  

   if (piece == 0) {
      cout << "C'est à l'ordinateur de commencer" << endl;
        
    } else {
       cout << "C'est à vous de commencer" <<endl;
        
    }

 

        while (true) {
          
          int col;
          int bestMove ;
          if (piece == 1) {
           cout << "Entrez la colonne où vous voulez jouer (0-6) : ";
           cin >> col;
           while (col < 0 || col > 6 || jeu.plein(col)) {
                    cout << "Coup invalide. Entrez une colonne valide (0-6) : " << endl;
                    cin >> col;
                  }
            jeu.jouer(col, -1);
            jeu.affichage();
            if (jeu.victoire(-1)) {
              cout << "Vous avez gagné!" << endl;
              break;
            }
            
          }
          else{  
             
              jeu.JeuOrdi(bestMove, 0);
              jeu.jouer(bestMove, 1);
            cout<<"l'ordinateur joue dans la colonne : "<<bestMove<<endl;
              jeu.affichage();
              if (jeu.victoire(1)) {
                  cout << "L'ordinateur a gagné!" << endl;
                  break;
              }

            }
          
               if(jeu.pleine())
               {
                cout<<" match null "<<endl;
                 break;
               }

               piece=(piece==0)?1:0;
              
        
    }
    return 0;
}

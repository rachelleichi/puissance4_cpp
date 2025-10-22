#include "Puissance4.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Puissance4::Puissance4(int h) {
  hmax = h;

  for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 7; ++j)
      T[i][j] = 0;

  for (int j = 0; j < 7; ++j)
    Col[j] = -1;
}

void Puissance4::affichage() {
    cout << "  0   1   2   3   4   5   6" << endl;
    for (int i = 5; i >= 0; --i) {
        cout << "|";
        for (int j = 0; j < 7; ++j) {
            if (T[i][j] == 1) {
                cout << " 0 |";  // Ordinateur
            } else if (T[i][j] == -1) {
                cout << " X |";  // Joueur
            } else {
                cout << "   |";  // Case vide
            }
        }
        cout << "   Ligne " << i << endl;
    }
    cout << "-----------------------------" << endl;
}
/*
void Puissance4::affichage() {

  cout << "  0   1   2   3   4   5   6" << endl;
  for (int i = 5; i >= 0; --i) {
    cout << "|";
    for (int j = 0; j < 7; ++j) {

      cout << " " << T[i][j] << " |";
    }
    cout << "   Ligne " << i << endl;
  }
  cout << "-----------------------------" << endl;
}*/

bool Puissance4::pleine() {
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 7; ++j) {
      if (T[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

bool Puissance4::plein(int &j) { return (Col[j] >= 5); }

int Puissance4 ::col(int j) { return Col[j]; }


void Puissance4::jouer(int j, int joueur) {
  int r = col(j) + 1;
  T[r][j] = joueur;
  Col[j]++;
}


void Puissance4::dejouer(int j) {
  int r = col(j);
  T[r][j] = 0;
  Col[j]--;
}


bool Puissance4::colonnes(int joueur) {
  bool vic = false;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      if (T[i][j] == joueur && T[i][j + 1] == joueur && T[i][j + 2] == joueur &&
          T[i][j + 3] == joueur) {

        vic= true;
      }
    }
  }
  return vic;
}


bool Puissance4::lignes(int joueur) {
  bool vic = false;
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 7; j++) {
      if (T[i][j] == joueur && T[i + 1][j] == joueur && T[i + 2][j] == joueur &&
          T[i + 3][j] == joueur) {

        vic= true;
      }
    }
  }
  return vic;
}



bool Puissance4::diagonale(int joueur) {
  bool vic = false;
  // Check diagonal (top-left to bottom-right)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (T[i][j] == joueur && T[i + 1][j + 1] == joueur &&
          T[i + 2][j + 2] == joueur && T[i + 3][j + 3] == joueur) {

        vic= true;
      }
    }
  }

  // Check diagonal (top-right to bottom-left)
  for (int i = 0; i < 3; i++) {
    for (int j = 3; j < 7; j++) {
      if (T[i][j] == joueur && T[i + 1][j - 1] == joueur &&
          T[i + 2][j - 2] == joueur && T[i + 3][j - 3] == joueur) {

        vic= true;
      }
    }
  }
  
  return vic;
}


bool Puissance4::victoire(int joueur){
  if (lignes(joueur) || colonnes(joueur) || diagonale(joueur)) {
    return true;
  }
  return false;

}


bool Puissance4::coupgagnant(int joueur, int &bestMove) {
  // je parcours toutes les lignes apr les colonnes apr les diago
  for (int i = 0; i < 7; i++) {
    if (!plein(i)) {

      jouer(i, joueur); // i num colomn
      if (victoire(joueur)) {
        bestMove = i;
        dejouer(i);
        return true;
      }
      
      dejouer(i);
    }
  }

  return false;
}





int Puissance4::direction1(int joueur, int col, int line) {
  int result = 5;
  int i = line;
  for (int j = col + 1, count = 0; j < 7 && T[i][j] != (-joueur) && count < 3;

       j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int j = col - 1, count = 0; j >= 0 && T[i][j] != (-joueur) && count < 3;
       j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// vertical
int Puissance4::direction2(int joueur, int col, int line) {
  int result = 5;
  int j = col;
  for (int i = line + 1, count = 0; i < 6 && count < 3; i++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
  }
  for (int i = line - 1, count = 0; i >= 0 && T[i][j] != (-joueur) && count < 3;
       i--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// diagonale1 "/"
int Puissance4::direction3(int joueur, int col, int line) {
  int result = 5;
  for (int i = line + 1, j = col + 1, count = 0;
       i < 6 && j < 7 && T[i][j] != (-joueur) && count < 3; i++, j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int i = line - 1, j = col - 1, count = 0;
       i >= 0 && j >= 0 && T[i][j] != (-joueur) && count < 3;
       i--, j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// diagonale2 "\"
int Puissance4::direction4(int joueur, int col, int line) {
  int result = 5;
  for (int i = line + 1, j = col - 1, count = 0;
       i < 6 && j >= 0 && T[i][j] != (-joueur) && count < 3;
       i++, j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int i = line - 1, j = col + 1, count = 0;
       i >= 0 && j < 7 && T[i][j] != (-joueur) && count < 3;
       i--, j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

int Puissance4::evaluation(int joueur, int j) {
  int i = Col[j] + 1;
  int eval1 = direction1(joueur, j, i);
  int eval2 = direction2(joueur, j, i);
  int eval3 = direction3(joueur, j, i);
  int eval4 = direction4(joueur, j, i);
  if (eval1 >= 20 || eval2 >= 20 || eval3 >= 20 || eval4 >= 20)
    return (joueur)*1000;
  else
    return (eval1 + eval2 + eval3 + eval4);
}







int Puissance4::JeuOrdi(int &bestMove, int niveau) {

  int arg = bestMove;
  int joueur = 1;
  /* Si le plateau est rempli au moment où l’ordinateur doit jouer alors il
  s’agit d’un match nul.
  */
  bool p = true;
  for (int j = 0; j < 7; j++) {
    p &= plein(j);
  }
  if (p)
    return (0);
  /* Si l’ordinateur a un coup gagnant, celui-ci est rangé dans bestMove, et
  la partie est terminée.
  */
  if (coupgagnant(joueur, bestMove)) {
    return (1000);
  }
  /* Si ‘‘niveau’’ a atteint le maximum hmax alors évaluer l’état du jeu en
  faisant la somme des évaluations des coups réalisables par l’ordinateur.
  */
  if (niveau == hmax) {
    int S = 0;
    for (int j = 0; j < 7; j++) {
      if (not plein(j)) {
        /* jouer dans la colonne j
         */
        jouer(j, joueur);
        S = S + evaluation(joueur, j);
        /* Remettre la colonne j dans son état initial
         */
        dejouer(j);
        if (hmax == 0)
          bestMove = j;
      }
    }
    return (S);
  }
  int val = (-1000);
  /* Sinon pour chaque colonne j où il est possible de jouer,...
   */
  for (int j = 0; j < 7; j++) {
    if (!plein(j)) {
      jouer(j, joueur);
      /* évaluer les réponses possibles de l’adversaire si l’ordinateur joue
      dans la colonne j.
      */
      int res = JeuHumain(arg, niveau + 1);
      dejouer(j);
      /* Stocker dans ‘‘val’’ la valeur maximale ‘‘res’’, correspondant au
      coup de l’ordinateur le plus favorable pour lui
      */
      if (res >= val) {
        val = res;
        bestMove = j;
      }
    }
  }
  return (val);
}

int Puissance4::JeuHumain(int &bestMove, int niveau) {
  /* arg est un argument additionel passé à l’appel récursif à JeuHumain.*/
  int arg = bestMove;
  int joueur = -1;
  /* Si le plateau est rempli au moment où l’ordinateur doit jouer alors il
  s’agit d’un match nul.
  */
  bool p = true;
  for (int j = 0; j < 7; j++) {
    p &= plein(j);
  }
  if (p)
    return (0);
  /* Si l’ordinateur a un coup gagnant, celui-ci est rangé dans bestMove, et
  la partie est terminée.
  */
  if (coupgagnant(joueur, arg)) {
    return (-1000);
  }
  /* Si ‘‘niveau’’ a atteint le maximum hmax alors évaluer l’état du jeu en
  faisant la somme des évaluations des coups réalisables par l’ordinateur.
  */
  if (niveau == hmax) {
    int S = 0;
    for (int j = 0; j < 7; j++) {
      if (not plein(j)) {
        /* jouer dans la colonne j
         */
        jouer(j, joueur);
        S = S + evaluation(joueur, j);
        /* Remettre la colonne j dans son état initial
         */
        dejouer(j);
      }
    }
    return (S);
  }
  int val = 1000;
  /* Sinon pour chaque colonne j où il est possible de jouer,...
   */
  for (int j = 0; j < 7; j++) {
    if (!plein(j)) {
      jouer(j, joueur);
      /* évaluer les réponses possibles de l’adversaire si l’ordinateur joue
      dans la colonne j.
      */
      int res = JeuOrdi(arg, niveau + 1);
      dejouer(j);
      /* Stocker dans ‘‘val’’ la valeur maximale ‘‘res’’, correspondant au
      coup de l’ordinateur le plus favorable pour lui
      */
      if (res <= val) {
        val = res;
        arg = j;
      }
    }
  }
  return (val);
}

#ifndef CBC51645_2202_4D90_BB6F_8AB65B182AC9
#define CBC51645_2202_4D90_BB6F_8AB65B182AC9
#ifndef PUISSANCE4_H
#define PUISSANCE4_H
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Puissance4 {
private:
    int T[6][7];
    int Col[7];
    int hmax;

public:
    Puissance4(int h);
    int colonne(int j);
    void affichage();
    bool plein(int &j);
    int col(int j);
    bool pleine();
    bool diagonale(int joueur);
    bool lignes(int joueur);
    bool colonnes(int joueur);
    bool victoire(int joueur);
    bool coupgagnant(int joueur, int &bestMove);
    int direction1(int joueur, int col, int line);
    int direction2(int joueur, int col, int line);
    int direction3(int joueur, int col, int line);
    int direction4(int joueur, int col, int line);
    int evaluation(int joueur, int j);
    void jouer(int j, int joueur);
    void dejouer(int j);
    int JeuOrdi(int& bestMove, int niveau);
    int JeuHumain(int& bestMove, int niveau);
};


#endif // PUISSANCE4_H


#endif /* CBC51645_2202_4D90_BB6F_8AB65B182AC9 */

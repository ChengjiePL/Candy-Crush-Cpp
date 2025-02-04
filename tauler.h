#ifndef TAULER_H
#define TAULER_H
#include "candy.h"
#include "posicio.h"
#include <iostream>

using namespace std;

class Tauler
{
public:
    Tauler()
    {
        nNewCandy = 0;
        newCandy[0] = Candy(VERMELL, NORMAL);
        newCandy[1] = Candy(TARONJA, NORMAL);
        newCandy[2] = Candy(GROC, NORMAL);
        newCandy[3] = Candy(BLAU, NORMAL);
        newCandy[4] = Candy(VERD, NORMAL);
        newCandy[5] = Candy(LILA, NORMAL);
    }
    void setCandy(Candy candy, Posicio& p) {
        m_tauler[p.getFila()][p.getColumna()] = candy;
    }

    void setCandy(const Posicio& p, const Candy& c) {
        m_tauler[p.getFila()][p.getColumna()] = c;
    }

    void setCounter(int counter) { m_counter = counter; }

    Candy getCandy(int fila, int columna) const { return m_tauler[fila][columna]; }

    Candy getCandy(const Posicio& p) const { return m_tauler[p.getFila()][p.getColumna()]; }

    void swapCandy(const Posicio& p1, const Posicio& p2);

    void eliminacioCandys(const Posicio* posiciones, const int& nPosiciones);

    void pullCandyDown();

    void omplirForats();


    Posicio* candysCompatibles(const Posicio& posicion, int& nPosiciones);
    void addCandysToEquivalents(const Posicio* candysCompatibles, int nCandysCompatibles, Posicio* candysEquivalents, int& nPosiciones);
    void addEquivalentCandys(Posicio* candysEquivalents, int& nPosiciones);

    Posicio* candysCompatibles(const Posicio* posiciones, int& nPosiciones);

    void setRallats(const Posicio* posicionesCombinaciones, const int& nPosiciones, const Posicio& pos1, const Posicio& pos2);
    int findMinFila(const Posicio* posiciones, const int& nPosiciones);
    int findMinColumna(const Posicio* posiciones, const int& nPosiciones);
    bool checkRallatsVertical(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nRallats, const Posicio& pos1, const Posicio& pos2);
    bool checkRallatsHoritzontal(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nRallats, const Posicio& pos1, const Posicio& pos2);



    Posicio* posAOmplir(const Posicio* posiciones, int& nPosicions);

    void numeroCandyNueva() { nNewCandy = 0; }

    Candy NewCandy();
    void deleteCandy(const Posicio& p) { setCandy(p, Candy(getCandy(p).getColor(), NO_TIPUS)); }
    Posicio* getCandysCompHorizontal(const Posicio& p, int& nCaramelosCompatiblesHorizontal);
    Posicio* getCandysCompVertical(const Posicio& p, int& nCaramelosCompatiblesVertical);
    Posicio* getLiniaX(const int& fila) const;
    Posicio* getLiniaY(const int& columna) const;

    void dibuixa();


    void invertirCoordenadas(const Posicio& pos)
    {
        int temp = pos.getColumna();
        const_cast<Posicio&>(pos).setColumna(pos.getFila());
        const_cast<Posicio&>(pos).setFila(temp);
    }

    pair<Posicio*, int> buscarCaramelosCompatiblesEnTablero();

    bool checkBombesVertical(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nBombes, const Posicio& pos1, const Posicio& pos2);
    bool checkBombesHoritzontal(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nBombes, const Posicio& pos1, const Posicio& pos2);


private:
    Candy m_tauler[MAX_FILES][MAX_COLUMNES];
    Candy newCandy[6];
    int nNewCandy;
    int m_counter = 0;
};

#endif

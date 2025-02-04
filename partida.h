#ifndef PARTIDA_H
#define PARTIDA_H

#include "tauler.h"
#include <string>
#include "InfoJoc.h"
#include "GraphicManager.h"

using namespace std;

class Partida {
public:
	Partida() {};
	void inicialitza(const string& nomFitxer);
	void escriuTauler(const string& nomFitxer);

	void dibuixa();

	ColorCandy candy(const Posicio& pos1) { return m_tauler.getCandy(pos1).getColor(); }


	pair<Posicio*, int> iniciaMoviment(const Posicio& pos1, const Posicio& pos2);
	void continuaMoviment(const Posicio& pos1, const Posicio& pos2, Posicio* posicionsCompatibles, int nPosicionsCompatibles);
	void continuaMoviment2(const Posicio& pos1, const Posicio& pos2, Posicio* posicionsCompatibles, int nPosicionsCompatibles);

private:
	Tauler m_tauler;
};

#endif

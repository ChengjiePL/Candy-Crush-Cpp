#include "posicio.h"

bool Posicio::esProximo(const Posicio& p) const
{
	int puntFila = abs(p.getFila() - m_fila);
	int puntColumna = abs(p.getColumna() - m_columna);
	return (puntFila + puntColumna == 1);
}

bool Posicio::posicioCorrecte(const Posicio* posicions, const int& nPosicions) const
{
	int i = 0;
	while (i < nPosicions && (m_fila != posicions[i].getFila() || m_columna != posicions[i].getColumna())) {
		i++;
	}
	return (i < nPosicions);
}

bool Posicio::columnaIgual(const Posicio& p) const
{
	if (p.getColumna() == m_columna)
		return false;
	else
		return true;
}


		
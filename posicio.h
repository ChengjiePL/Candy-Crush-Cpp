#ifndef POSICIO_H
#define POSICIO_H

#include "definicions.h"
#include <math.h>
#include <utility>

class Posicio {
public:
    Posicio() : m_fila(-1), m_columna(-1), m_color(NO_COLOR) {}
    Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}
    void set(int fila, int columna) {
        m_fila = fila;
        m_columna = columna;
    }
    void setColumna(int columna) { m_columna = columna; }
    void setFila(int fila) { m_fila = fila; }
    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }

    int getColor() const { return m_color; }

    bool esProximo(const Posicio& p) const;

    bool posicioCorrecte(const Posicio* posicions, const int& nPosicions) const;
    bool operator==(const Posicio& p) const {
        return (m_fila == p.m_fila && m_columna == p.m_columna);
    }

    bool operator!=(const Posicio& p) const { return !(*this == p); }
    bool columnaIgual(const Posicio& p) const;



private:
    int m_fila;
    int m_columna;
    ColorCandy m_color;
};

#endif

#ifndef Joc_hpp
#define Joc_hpp

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "partida.h"

using namespace std;

typedef enum
{
    ESTAT_JOC_ESPERA,
    ESTAT_JOC_INTERCANVI,
    ESTAT_JOC_MOVIMENTS,
    ESTAT_JOC_ESPERA_DESCENS,
    ESTAT_JOC_ESPERA_ELIMINACIO,
    ESTAT_FINAL
} EstatJoc;


class Joc 
{
public:
    Joc() : m_temps(0), m_estat(ESTAT_JOC_ESPERA) {};
    
    bool estanAlLado(const Posicio& p1, const Posicio& p2);

    void inicialitza(const string& nomFitxerInicial);
    void actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime);

private:
    double m_temps;
    Partida m_partida;
    Posicio p1, p2;
    EstatJoc m_estat;
    pair<Posicio*, int> resultado;
    int counter = 10;
    int punts = 0;
    int m_objectiu = 10;
};

#endif /* Joc_hpp */

#include "partida.h"
#include <fstream>
#include <iostream>

void Partida::inicialitza(const string& nomFitxer) {
    // abrimos el archivo
    ifstream fitxer(nomFitxer);

    if (!fitxer.is_open()) {
        return;
    }
    string linia;
    // Llamamos la funcion que nos proporciona la biblioteca de c++ (getline), lo
    // utilizamos para poder leer una linea completa del archivo y almacenarla en
    // la variable linea
    getline(fitxer, linia);

    for (int f = 0; f < MAX_FILES; f++) {
        // Comprovamos si se a podido leer la linea
        if (!getline(fitxer, linia)) {
            return;
        }

        for (int c = 0; c < MAX_COLUMNES; c++) {
            // Conseguimos el carácter correspondiente con su columna y fila
            // La funcion at() devuelve el carácter que se encuentra en la posición
            // especificada como argumento

            // Como el archivo esta separado por espacios en blanco lo multiplicamos por 2
            char ll = linia.at(c * 2);
            ColorCandy color = NO_COLOR;

            switch (ll) {

            case 'R':
                color = VERMELL;
                break;
            case 'O':
                color = TARONJA;
                break;
            case 'Y':
                color = GROC;
                break;
            case 'G':
                color = VERD;
                break;
            case 'B':
                color = BLAU;
                break;
            case 'P':
                color = LILA;
                break;
            case 'p':
                color = ESPECIAL;
                break;
            case 'E':
                color = NO_COLOR;
                break;
            }
            // Inicializamos una variable de tipo Posicion a partir de la posicion correspondiente
            Posicio p(f, c);
            Candy caramelo;
            // Añadimos el caramelo al tablero
            caramelo.setTipus(NORMAL);
            caramelo.setColor(color);
            m_tauler.setCandy(caramelo, p);
        }
    }
    // Cerramos el archivo
    fitxer.close();
}

void Partida::escriuTauler(const string& nomFitxer)
{
    // Abrimos el archivo para escribir en él
    ofstream fitxer(nomFitxer);

    // Verificamos si se pudo abrir el archivo
    if (!fitxer.is_open()) {
        return;
    }

    // Recorremos las filas del tablero
    for (int fila = 0; fila < MAX_FILES; fila++) {
        string lletres;
        // Recorremos las columnas del tablero
        for (int columna = 0; columna < MAX_COLUMNES; columna++) {
            Posicio pos(fila, columna);
            // Obtenemos el caramelo de la posición actual
            Candy candy = m_tauler.getCandy(pos);
            // letra por defecto
            char c = 'E';
            // Asignamos una letra según el color del caramelo
            switch (candy.getColor())
            {
            case VERMELL:
                c = 'R';
                break;
            case TARONJA:
                c = 'O';
                break;
            case GROC:
                c = 'Y';
                break;
            case BLAU:
                c = 'B';
                break;
            case VERD:
                c = 'G';
                break;
            case LILA:
                c = 'P';
                break;
            }
            // Agregamos la letra a la línea actual
            // Comprovamos si no es la ultima columna para poder añadirle un espacio

            if (candy.getTipus() == RATLLAT_HORIZONTAL || candy.getTipus() == RATLLAT_VERTICAL)
            {
                c = tolower(c);
            }

            lletres += c;
            if (columna < MAX_COLUMNES - 1) {
                lletres += ' ';
            }
        }
        // Escribimos la línea en el archivo
        fitxer << lletres << endl;
    }
    // Cerramos el archivo y reiniciamos creando una candy nueva
    fitxer.close();
    m_tauler.numeroCandyNueva();
}


pair<Posicio*, int> Partida::iniciaMoviment(const Posicio& pos1, const Posicio& pos2)
{
    m_tauler.invertirCoordenadas(pos1);
    m_tauler.invertirCoordenadas(pos2);
    m_tauler.swapCandy(pos1, pos2);

    int nPosicionsCompatibles = 2;
    Posicio* posicionsCompatibles = m_tauler.candysCompatibles(new Posicio[nPosicionsCompatibles]{ pos1, pos2 }, nPosicionsCompatibles);

    if (nPosicionsCompatibles == 0)
    {
        m_tauler.swapCandy(pos1, pos2);
        return make_pair(nullptr, 0);
    }

    return make_pair(posicionsCompatibles, nPosicionsCompatibles);
}

void Partida::continuaMoviment(const Posicio& pos1, const Posicio& pos2, Posicio* posicionsCompatibles, int nPosicionsCompatibles)
{

    m_tauler.eliminacioCandys(posicionsCompatibles, nPosicionsCompatibles);

    m_tauler.setRallats(posicionsCompatibles, nPosicionsCompatibles, pos1, pos2);

}

void Partida::continuaMoviment2(const Posicio& pos1, const Posicio& pos2, Posicio* posicionsCompatibles, int nPosicionsCompatibles)
{
    m_tauler.pullCandyDown();

    m_tauler.omplirForats();



    do
    {
        posicionsCompatibles = m_tauler.candysCompatibles(m_tauler.posAOmplir(posicionsCompatibles, nPosicionsCompatibles), nPosicionsCompatibles);

        m_tauler.eliminacioCandys(posicionsCompatibles, nPosicionsCompatibles);

        m_tauler.setRallats(posicionsCompatibles, nPosicionsCompatibles, Posicio(), Posicio());

        m_tauler.pullCandyDown();

        m_tauler.omplirForats();



        pair<Posicio*, int> resultado = m_tauler.buscarCaramelosCompatiblesEnTablero();

        // Obtener el array de posiciones y el número de posiciones
        Posicio* posicionesCompatibles = resultado.first;
        int nPosicionesCompatibles = resultado.second;

        // Verificar si se encontraron posiciones compatibles
        if (nPosicionesCompatibles > 0)
        {
            // Llamada a la función eliminacioCandys para eliminar los caramelos en las posiciones compatibles
            m_tauler.eliminacioCandys(posicionesCompatibles, nPosicionesCompatibles);
            m_tauler.setRallats(posicionsCompatibles, nPosicionsCompatibles, pos1, pos2);
            m_tauler.pullCandyDown();
            m_tauler.omplirForats();



            // Liberar la memoria del array de posiciones
            delete[] posicionesCompatibles;
        }
    } while (nPosicionsCompatibles != 0);

    pair<Posicio*, int> resultado = m_tauler.buscarCaramelosCompatiblesEnTablero();

    // Obtener el array de posiciones y el número de posiciones
    Posicio* posicionesCompatibles = resultado.first;
    int nPosicionesCompatibles = resultado.second;

    // Verificar si se encontraron posiciones compatibles
    if (nPosicionesCompatibles > 0)
    {
        // Llamada a la función eliminacioCandys para eliminar los caramelos en las posiciones compatibles
        m_tauler.eliminacioCandys(posicionesCompatibles, nPosicionesCompatibles);
        m_tauler.setRallats(posicionsCompatibles, nPosicionsCompatibles, pos1, pos2);
        m_tauler.pullCandyDown();
        m_tauler.omplirForats();



        // Liberar la memoria del array de posiciones
        delete[] posicionesCompatibles;
    }
}

void Partida::dibuixa()
{
    m_tauler.dibuixa();
}

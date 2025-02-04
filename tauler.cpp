#include "tauler.h"
#include <vector>

void Tauler::swapCandy(const Posicio& p1, const Posicio& p2)
{
    Candy candy1 = getCandy(p1);
    Candy candy2 = getCandy(p2);

    // Intercambiar los caramelos
    setCandy(p1, candy2);
    setCandy(p2, candy1);
}

void Tauler::eliminacioCandys(const Posicio* posiciones, const int& nPosiciones)
{
    for (int i = 0; i < nPosiciones; i++)
    {
        deleteCandy(posiciones[i]);
    }
}


void Tauler::pullCandyDown()
{
    for (int j = 0; j < MAX_COLUMNES; j++)
    {
        int emptyCount = 0;  // Contador de casillas vacías

        for (int i = MAX_FILES - 1; i >= 0; i--)
        {
            if (getCandy(i, j).getTipus() == NO_TIPUS)
            {
                emptyCount++;  // Incrementar el contador de casillas vacías
            }
            else if (emptyCount > 0)
            {
                // Realizar el desplazamiento hacia abajo del caramelo no vacío
                setCandy(Posicio(i + emptyCount, j), getCandy(i, j));
                setCandy(Posicio(i, j), Candy(getCandy(i, j).getColor(), NO_TIPUS));
            }
        }
        
        // Restablecer el contador de casillas vacías después de procesar una columna
        emptyCount = 0;
    }
}


void Tauler::omplirForats()
{
    int f = MAX_FILES - 1;
    while (f >= 0)
    {
        int c = 0;
        while (c < MAX_COLUMNES)
        {
            if (m_tauler[f][c].getTipus() == NO_TIPUS)
            {
                setCandy(Posicio(f, c), NewCandy());
            }
            c++;
        }
        f--;
    }
}

Posicio* Tauler::candysCompatibles(const Posicio& posicion, int& nPosiciones)
{
    nPosiciones = 0;
    int nCandysCompatiblesHorizontal;
    int nCandysCompatiblesVertical;

    // Obtener los caramelos compatibles horizontalmente y verticalmente
    Posicio* candysCompatiblesHorizontal = getCandysCompHorizontal(posicion, nCandysCompatiblesHorizontal);
    Posicio* candysCompatiblesVertical = getCandysCompVertical(posicion, nCandysCompatiblesVertical);

    // Crear un array para almacenar las posiciones equivalentes
    Posicio* candysEquivalents = new Posicio[LIMIT_TAULER];

    // Agregar los caramelos compatibles horizontalmente al array de equivalentes
    addCandysToEquivalents(candysCompatiblesHorizontal, nCandysCompatiblesHorizontal, candysEquivalents, nPosiciones);
    // Agregar los caramelos compatibles verticalmente al array de equivalentes
    addCandysToEquivalents(candysCompatiblesVertical, nCandysCompatiblesVertical, candysEquivalents, nPosiciones);

    if (nPosiciones == 0)
        return nullptr;

    // Agregar la posición original al array de equivalentes
    candysEquivalents[nPosiciones++] = posicion;

    // Agregar las posiciones equivalentes a los caramelos rallados
    addEquivalentCandys(candysEquivalents, nPosiciones);

    delete[] candysCompatiblesHorizontal;
    delete[] candysCompatiblesVertical;

    // Crear un nuevo array para almacenar todas las posiciones equivalentes
    Posicio* totalCandysEquivalents = new Posicio[nPosiciones];
    for (int i = 0; i < nPosiciones; i++)
    {
        totalCandysEquivalents[i] = candysEquivalents[i];
    }
    delete[] candysEquivalents;

    return totalCandysEquivalents;
}

void Tauler::addCandysToEquivalents(const Posicio* candysCompatibles, int nCandysCompatibles, Posicio* candysEquivalents, int& nPosiciones)
{
    // Verificar que no se exceda el tamaño máximo del array de posiciones equivalentes
    const int MAX_EQUIVALENTS = LIMIT_TAULER;
    int maxPosiciones = MAX_EQUIVALENTS - nPosiciones;

    // Agregar los caramelos compatibles al array de equivalentes
    int i = 0;
    while (i < nCandysCompatibles && nPosiciones < MAX_EQUIVALENTS)
    {
        candysEquivalents[nPosiciones++] = candysCompatibles[i];
        i++;
    }
}

void Tauler::addEquivalentCandys(Posicio* candysEquivalents, int& nPosiciones)
{
    int nCandysNoRallats = nPosiciones;
    for (int i = 0; i < nCandysNoRallats; i++)
    {
        // Obtener el caramelo en la posición actual
        Candy candy = getCandy(candysEquivalents[i]);

        // Comprobar si el caramelo es horizontalmente rallado
        if (candy.getTipus() == RATLLAT_HORIZONTAL)
        {
            // Agregar las posiciones equivalentes en la misma fila
            for (int j = 0; j < MAX_COLUMNES; j++)
            {
                Posicio pos(candysEquivalents[i].getFila(), j);
                candysEquivalents[nPosiciones++] = pos;
            }
        }
        // Comprobar si el caramelo es verticalmente rallado
        else if (candy.getTipus() == RATLLAT_VERTICAL)
        {
            // Agregar las posiciones equivalentes en la misma columna
            for (int j = 0; j < MAX_FILES; j++)
            {
                Posicio pos(j, candysEquivalents[i].getColumna());
                candysEquivalents[nPosiciones++] = pos;
            }
        }
        // Comprobar si el caramelo es una bomba y agregar los caramelos del mismo color
        else if (candy.getTipus() == BOMBA)
        {
            // Agregar las posiciones de los caramelos del mismo color al array de equivalentes
            for (int fila = 0; fila < MAX_FILES; fila++)
            {
                for (int columna = 0; columna < MAX_COLUMNES; columna++)
                {
                    // Obtener el caramelo en la posición actual
                    Candy candyActual = getCandy(Posicio(fila, columna));

                    // Comprobar si el caramelo actual tiene el mismo color que el caramelo cambiado
                    if (candyActual.getColor() == GROC)
                    {
                        candysEquivalents[nPosiciones++] = Posicio(fila, columna);
                    }
                }
            }
        }
    }
}



pair<Posicio*, int> Tauler::buscarCaramelosCompatiblesEnTablero()
{
    int nPosiciones = 0;
    int nCandysCompatiblesHorizontal;
    int nCandysCompatiblesVertical;

    Posicio* candysEquivalents = new Posicio[LIMIT_TAULER];

    // Recorrer el tablero para buscar caramelos compatibles
    for (int fila = 0; fila < MAX_FILES; fila++)
    {
        for (int columna = 0; columna < MAX_COLUMNES; columna++)
        {
            Posicio posicion(fila, columna);

            // Obtener los caramelos compatibles horizontalmente y verticalmente
            Posicio* candysCompatiblesHorizontal = getCandysCompHorizontal(posicion, nCandysCompatiblesHorizontal);
            Posicio* candysCompatiblesVertical = getCandysCompVertical(posicion, nCandysCompatiblesVertical);

            // Agregar los caramelos compatibles horizontalmente al array de equivalentes
            addCandysToEquivalents(candysCompatiblesHorizontal, nCandysCompatiblesHorizontal, candysEquivalents, nPosiciones);
            // Agregar los caramelos compatibles verticalmente al array de equivalentes
            addCandysToEquivalents(candysCompatiblesVertical, nCandysCompatiblesVertical, candysEquivalents, nPosiciones);

            delete[] candysCompatiblesHorizontal;
            delete[] candysCompatiblesVertical;
        }
    }

    if (nPosiciones == 0)
    {
        delete[] candysEquivalents;
        return make_pair(nullptr, 0);
    }

    // Crear un nuevo array para almacenar todas las posiciones equivalentes
    Posicio* totalCandysEquivalents = new Posicio[nPosiciones];
    for (int i = 0; i < nPosiciones; i++)
    {
        totalCandysEquivalents[i] = candysEquivalents[i];
    }
    delete[] candysEquivalents;

    return make_pair(totalCandysEquivalents, nPosiciones);
}


Posicio* Tauler::candysCompatibles(const Posicio* posiciones, int& nPosiciones)
{
    if (posiciones == nullptr)
        return nullptr;

    int nPos = nPosiciones;
    nPosiciones = 0;

    Posicio* candysEquivalents = new Posicio[LIMIT_TAULER];

    for (int i = 0; i < nPos; i++)
    {
        if (!posiciones[i].posicioCorrecte(candysEquivalents, nPosiciones))
        {
            int nPosCandysCompatibles = 0;
            Posicio* posCandysCompatibles = candysCompatibles(posiciones[i], nPosCandysCompatibles);

            for (int j = 0; j < nPosCandysCompatibles; j++)
            {
                candysEquivalents[nPosiciones++] = posCandysCompatibles[j];
            }

            if (posCandysCompatibles == nullptr)
                delete[] posCandysCompatibles;
        }
    }

    return candysEquivalents;
}



// Función principal para establecer los caramelos rallados
void Tauler::setRallats(const Posicio* posicionesCombinaciones, const int& nPosiciones, const Posicio& pos1, const Posicio& pos2)
{
    // Verificar si el número de posiciones combinadas es válido
    if (nPosiciones <= MIN_MATCHING || nPosiciones >= 10)
        return;

    int nRallats = nPosiciones;
    bool horitzontal = true;

    // Recorrer todas las posiciones combinadas
    for (int i = 0; i < nPosiciones; i++)
    {
        int f = posicionesCombinaciones[i].getFila();
        int c = posicionesCombinaciones[i].getColumna();

        /*if (checkBombesVertical(posicionesCombinaciones, nPosiciones, f, c, nRallats, pos1, pos2))
        {
            return;
        }

        if (checkBombesHoritzontal(posicionesCombinaciones, nPosiciones, f, c, nRallats, pos1, pos2))
        {
            return;
        }*/

        // Verificar si se pueden establecer caramelos rallados horizontalmente
        if (checkRallatsHoritzontal(posicionesCombinaciones, nPosiciones, f, c, nRallats, pos1, pos2))
            return; // Si se han establecido todos los caramelos rallados necesarios, salir de la función

        // Verificar si se pueden establecer caramelos rallados verticalmente
        if (checkRallatsVertical(posicionesCombinaciones, nPosiciones, f, c, nRallats, pos1, pos2))
            return; // Si se han establecido todos los caramelos rallados necesarios, salir de la función
    }
}

bool Tauler::checkBombesVertical(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nBombes, const Posicio& pos1, const Posicio& pos2)
{
    int nCandysColumna = 0;
    Posicio CandysColumna[MAX_FILES];

    // Recorrer las posiciones y encontrar los caramelos combinados en la columna especificada
    for (int i = 0; i < nPosiciones; i++)
    {
        if (columna == posicionesCombinaciones[i].getColumna())
            CandysColumna[nCandysColumna++] = posicionesCombinaciones[i];
    }

    if (nCandysColumna >= 5)
    {
        // Verificar si se especificaron dos posiciones para el caramelo bomba
        if (pos1 != Posicio() && pos2 != Posicio())
        {
            // Verificar si las posiciones tienen la misma columna
            if (pos1.columnaIgual(pos2))
            {
                // Establecer caramelos bomba en las filas entre las posiciones especificadas
                int minFila = std::min(pos1.getFila(), pos2.getFila());
                int maxFila = std::max(pos1.getFila(), pos2.getFila());

                for (int f = minFila; f <= maxFila; f++)
                {
                    m_tauler[f][columna] = Candy(m_tauler[f][columna].getColor(), BOMBA);
                    nBombes--;
                }
            }
        }
        else
        {
            // Establecer caramelos bomba en todas las filas de la columna especificada
            for (int f = 0; f < MAX_FILES; f++)
            {
                m_tauler[f][columna] = Candy(m_tauler[f][columna].getColor(), BOMBA);
                nBombes--;
            }
        }

        if (nBombes == 0)
            return true; // Si se han establecido todos los caramelos bomba necesarios, retornar verdadero
    }

    return false; // Si no se han establecido todos los caramelos bomba necesarios, retornar falso
}


bool Tauler::checkBombesHoritzontal(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nBombes, const Posicio& pos1, const Posicio& pos2)
{
    int nCandysFila = 0;
    Posicio CandysFila[MAX_COLUMNES];

    // Recorrer las posiciones y encontrar los caramelos combinados en la fila especificada
    for (int j = 0; j < nPosiciones; j++)
    {
        if (fila == posicionesCombinaciones[j].getFila())
            CandysFila[nCandysFila++] = posicionesCombinaciones[j];
    }

    if (nCandysFila >= 5)
    {
        // Verificar si se especificaron dos posiciones para el caramelo bomba
        if (pos1 != Posicio() && pos2 != Posicio())
        {
            // Verificar si las posiciones tienen la misma fila
            if (pos1.columnaIgual(pos2))
            {
                // Establecer caramelos bomba en las columnas entre las posiciones especificadas
                int minColumna = std::min(pos1.getColumna(), pos2.getColumna());
                int maxColumna = std::max(pos1.getColumna(), pos2.getColumna());

                for (int c = minColumna; c <= maxColumna; c++)
                {
                    m_tauler[fila][c] = Candy(m_tauler[fila][c].getColor(), BOMBA);
                    nBombes--;
                }
            }
        }
        else
        {
            // Establecer caramelos bomba en todas las columnas de la fila especificada
            for (int c = 0; c < MAX_COLUMNES; c++)
            {
                m_tauler[fila][c] = Candy(m_tauler[fila][c].getColor(), BOMBA);
                nBombes--;
            }
        }

        if (nBombes == 0)
            return true; // Si se han establecido todos los caramelos bomba necesarios, retornar verdadero
    }

    return false; // Si no se han establecido todos los caramelos bomba necesarios, retornar falso
}


// Comprueba si hay caramelos rallados en la dirección horizontal
bool Tauler::checkRallatsHoritzontal(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nRallats, const Posicio& pos1, const Posicio& pos2)
{
    int nCandysLinia = 0;
    Posicio CandysLinia[MAX_COLUMNES];

    // Recorrer las posiciones y encontrar los caramelos combinados en la fila especificada
    for (int j = 0; j < nPosiciones; j++)
    {
        if (fila == posicionesCombinaciones[j].getFila())
            CandysLinia[nCandysLinia++] = posicionesCombinaciones[j];
    }

    if (nCandysLinia >= MIN_CARAMEL_ESPECIAL)
    {
        TipusCandy tipusRallat;

        // Verificar si se especificaron dos posiciones para el caramelo rallado
        if (pos1 != Posicio() && pos2 != Posicio())
        {
            // Determinar el tipo de caramelo rallado en función de si las posiciones tienen la misma columna
            if (pos1.columnaIgual(pos2))
                tipusRallat = RATLLAT_HORIZONTAL;
            else
                tipusRallat = RATLLAT_VERTICAL;

            // Verificar si una de las posiciones especificadas es válida para establecer el caramelo rallado
            if (pos1.posicioCorrecte(CandysLinia, nCandysLinia))
                m_tauler[pos1.getFila()][pos1.getColumna()] = Candy(m_tauler[pos1.getFila()][pos1.getColumna()].getColor(), tipusRallat);
            else if (pos2.posicioCorrecte(CandysLinia, nCandysLinia))
                m_tauler[pos2.getFila()][pos2.getColumna()] = Candy(m_tauler[pos2.getFila()][pos2.getColumna()].getColor(), tipusRallat);
        }
        else
        {
            // Encontrar la columna mínima en la que se encuentran los caramelos combinados
            int minColumna = findMinColumna(CandysLinia, nCandysLinia);

            tipusRallat = RATLLAT_HORIZONTAL;

            // Establecer el caramelo rallado en la fila especificada y la columna mínima
            m_tauler[fila][minColumna] = Candy(m_tauler[fila][minColumna].getColor(), tipusRallat);
        }

        nRallats -= 4;
        if (nRallats >= 0)
            return true; // Si se han establecido todos los caramelos rallados necesarios, retornar verdadero
    }

    return false; // Si no se han establecido todos los caramelos rallados necesarios, retornar falso
}


// Comprueba si hay caramelos rallados en la dirección vertical
bool Tauler::checkRallatsVertical(const Posicio* posicionesCombinaciones, const int& nPosiciones, const int& fila, const int& columna, int& nRallats, const Posicio& pos1, const Posicio& pos2)
{
    int nCandysLinia = 0;
    Posicio CandysLinia[MAX_FILES];

    // Recorrer las posiciones y encontrar los caramelos combinados en la columna especificada
    for (int j = 0; j < nPosiciones; j++)
    {
        if (columna == posicionesCombinaciones[j].getColumna())
            CandysLinia[nCandysLinia++] = posicionesCombinaciones[j];
    }

    if (nCandysLinia >= MIN_CARAMEL_ESPECIAL)
    {
        TipusCandy tipusRallat;

        // Verificar si se especificaron dos posiciones para el caramelo rallado
        if (pos1 != Posicio() && pos2 != Posicio())
        {
            // Determinar el tipo de caramelo rallado en función de si las posiciones tienen la misma columna
            if (pos1.columnaIgual(pos2))
                tipusRallat = RATLLAT_HORIZONTAL;
            else
                tipusRallat = RATLLAT_VERTICAL;

            // Verificar si una de las posiciones especificadas es válida para establecer el caramelo rallado
            if (pos1.posicioCorrecte(CandysLinia, nCandysLinia))
                m_tauler[pos1.getFila()][pos1.getColumna()] = Candy(m_tauler[pos1.getFila()][pos1.getColumna()].getColor(), tipusRallat);
            else if (pos2.posicioCorrecte(CandysLinia, nCandysLinia))
                m_tauler[pos2.getFila()][pos2.getColumna()] = Candy(m_tauler[pos2.getFila()][pos2.getColumna()].getColor(), tipusRallat);
        }
        else
        {
            // Encontrar la fila mínima en la que se encuentran los caramelos combinados
            int minFila = findMinFila(CandysLinia, nCandysLinia);

            tipusRallat = RATLLAT_VERTICAL;

            // Establecer el caramelo rallado en la fila mínima y la columna especificada
            m_tauler[minFila][columna] = Candy(m_tauler[minFila][columna].getColor(), tipusRallat);
        }

        nRallats -= 4;
        if (nRallats >= 0)
            return true; // Si se han establecido todos los caramelos rallados necesarios, retornar verdadero
    }

    return false; // Si no se han establecido todos los caramelos rallados necesarios, retornar falso
}


// Encuentra el valor mínimo de columna en un conjunto de posiciones
int Tauler::findMinColumna(const Posicio* posiciones, const int& nPosiciones)
{
    int minColumna = MAX_COLUMNES; // Inicializamos la variable minColumna con un valor máximo para que cualquier valor de columna sea menor
    for (int j = 0; j < nPosiciones; j++)
    {
        if (posiciones[j].getColumna() < minColumna) // Comparamos la columna actual con el valor mínimo actual
            minColumna = posiciones[j].getColumna(); // Si la columna actual es menor, actualizamos el valor mínimo
    }

    return minColumna; // Devolvemos el valor mínimo de la columna
}


// Encuentra el valor mínimo de fila en un conjunto de posiciones
int Tauler::findMinFila(const Posicio* posiciones, const int& nPosiciones)
{
    int minFila = MAX_FILES; // Inicializamos la variable minFila con un valor máximo para que cualquier valor de fila sea menor
    for (int j = 0; j < nPosiciones; j++)
    {
        if (posiciones[j].getFila() < minFila) // Comparamos la fila actual con el valor mínimo actual
            minFila = posiciones[j].getFila(); // Si la fila actual es menor, actualizamos el valor mínimo
    }

    return minFila; // Devolvemos el valor mínimo de la fila
}


Posicio* Tauler::posAOmplir(const Posicio* posiciones, int& nPosicions)
{
    // Verificar si no se proporcionaron posiciones
    if (posiciones == nullptr)
        return nullptr;

    Posicio* posTotals = new Posicio[LIMIT_TAULER]; // Arreglo temporal para almacenar las posiciones totales
    int nPosTotals = 0; // Contador de posiciones totales

    // Recorrer las posiciones proporcionadas
    for (int i = 0; i < nPosicions; i++)
    {
        const Posicio& posActual = posiciones[i]; // Obtener la posición actual

        // Agregar la posición actual y todas las filas superiores al arreglo posTotals
        for (int fila = posActual.getFila(); fila >= 0; fila--)
        {
            posTotals[nPosTotals++] = Posicio(fila, posActual.getColumna());
        }
    }

    return posTotals;
}


Candy Tauler::NewCandy()
{
    Candy candy = newCandy[nNewCandy];
    if (nNewCandy < 5)
    {
        nNewCandy++;
    }
    else
    {
        nNewCandy = 0;
    }
    return candy;
}

Posicio* Tauler::getCandysCompHorizontal(const Posicio& p, int& nCaramelosCompatiblesHorizontal)
{
    nCaramelosCompatiblesHorizontal = 0; // Inicializar contador de caramelos compatibles
    Candy candy = getCandy(p.getFila(), p.getColumna()); // Obtener el caramelo en la posición dada
    Posicio* candysEquivalents = new Posicio[LIMIT_TAULER]; // Crear arreglo para almacenar las posiciones de los caramelos compatibles

    int columnaLeft = p.getColumna() - 1; // Inicializar columna izquierda una columna antes de la posición dada
    int columnaRight = p.getColumna() + 1; // Inicializar columna derecha una columna después de la posición dada

    // Bucle mientras haya caramelos compatibles en la dirección izquierda o derecha
    while (columnaLeft >= 0 || columnaRight < MAX_COLUMNES)
    {
        if (columnaLeft >= 0 && getCandy(p.getFila(), columnaLeft).candyCompatible(candy))
        {
            // Si hay un caramelo compatible en la dirección izquierda
            // Agregar su posición al arreglo de caramelos compatibles y aumentar el contador
            candysEquivalents[nCaramelosCompatiblesHorizontal++] = Posicio(p.getFila(), columnaLeft);
            columnaLeft--; // Mover a la siguiente columna izquierda
        }
        else if (columnaRight < MAX_COLUMNES && getCandy(p.getFila(), columnaRight).candyCompatible(candy))
        {
            // Si hay un caramelo compatible en la dirección derecha
            // Agregar su posición al arreglo de caramelos compatibles y aumentar el contador
            candysEquivalents[nCaramelosCompatiblesHorizontal++] = Posicio(p.getFila(), columnaRight);
            columnaRight++; // Mover a la siguiente columna derecha
        }
        else
        {
            break; // Salir del bucle si no se encuentra un caramelo compatible en ninguna dirección
        }
    }

    // Comprobar si se encontraron suficientes caramelos compatibles para formar una combinación válida
    if (nCaramelosCompatiblesHorizontal < MIN_MATCHING - 1)
    {
        nCaramelosCompatiblesHorizontal = 0; // Reiniciar el contador
        delete[] candysEquivalents; // Liberar la memoria del arreglo de caramelos compatibles
        return nullptr; // No hay suficientes caramelos compatibles, retornar nullptr
    }

    return candysEquivalents; // Retornar el arreglo de caramelos compatibles
}



Posicio* Tauler::getCandysCompVertical(const Posicio& p, int& nCaramelosCompatiblesVertical)
{
    nCaramelosCompatiblesVertical = 0; // Inicializar el contador de caramelos compatibles en vertical
    Candy candy = getCandy(p); // Obtener el caramelo en la posición dada
    Posicio* candysEquivalents = new Posicio[LIMIT_TAULER]; // Crear un array para almacenar las posiciones de los caramelos compatibles en vertical

    //int fila = p.getFila();  // Obtener la fila de la posición dada
    int filaUp = p.getFila() - 1; // Inicializar la fila superior
    int filaDown = p.getFila() + 1; // Inicializar la fila inferior



    // Recorrer las filas superiores e inferiores mientras sean válidas
    while (filaUp >= 0 || filaDown < MAX_FILES)
    {
        if (filaUp >= 0 && getCandy(filaUp, p.getColumna()).candyCompatible(candy))
        {
            // Si la fila superior (filaUp) es válida y el caramelo en esa posición es compatible,
            // se agrega la posición al array de candysEquivalents
            candysEquivalents[nCaramelosCompatiblesVertical++] = Posicio(filaUp, p.getColumna());
            filaUp--; // Se mueve a la siguiente fila superior
        }
        else if (filaDown < MAX_FILES && getCandy(filaDown, p.getColumna()).candyCompatible(candy))
        {
            // Si la fila inferior (filaDown) es válida y el caramelo en esa posición es compatible,
            // se agrega la posición al array de candysEquivalents
            candysEquivalents[nCaramelosCompatiblesVertical++] = Posicio(filaDown, p.getColumna());
            filaDown++; // Se mueve a la siguiente fila inferior
        }
        else
        {
            break; // Si no se cumple ninguna de las condiciones, se sale del ciclo
        }
    }

    if (nCaramelosCompatiblesVertical < MIN_MATCHING - 1)
    {
        delete[] candysEquivalents;  // Si el número de caramelos compatibles en vertical es menor al mínimo requerido,
        // se libera la memoria asignada al array de candysEquivalents y se reinicia el contador
        nCaramelosCompatiblesVertical = 0;
        return nullptr;  // Se devuelve nullptr para indicar que no hay caramelos compatibles suficientes en vertical
    }

    Posicio* TotalCandysEquivalents = new Posicio[nCaramelosCompatiblesVertical];  // Se crea un nuevo array con el tamaño exacto necesario
    for (int i = 0; i < nCaramelosCompatiblesVertical; i++)
    {
        TotalCandysEquivalents[i] = candysEquivalents[i];  // Se copian las posiciones de los caramelos compatibles en el nuevo array
    }

    delete[] candysEquivalents;  // Se libera la memoria asignada al array original

    return TotalCandysEquivalents;  // Se devuelve el array con las posiciones de los caramelos compatibles en vertical
}


Posicio* Tauler::getLiniaX(const int& fila) const
{
    Posicio* pos = new Posicio[MAX_COLUMNES];
    int i = 0;
    for (int c = 0; c < MAX_COLUMNES; c++)
    {
        pos[i++] = Posicio(fila, c);
    }
    return pos;
}

Posicio* Tauler::getLiniaY(const int& columna) const
{
    Posicio* pos = new Posicio[MAX_FILES];
    int i = 0;
    for (int f = 0; f < MAX_FILES; f++)
    {
        pos[i++] = Posicio(f, columna);
    }
    return pos;
}

void Tauler::dibuixa()
{
    for (int fila = 0; fila < MAX_FILES; fila++)
    {
        for (int columna = 0; columna < MAX_COLUMNES; columna++)
        {
            Candy caramelo = m_tauler[fila][columna];
            caramelo.dibuixa(columna, fila);
        }
    }
}
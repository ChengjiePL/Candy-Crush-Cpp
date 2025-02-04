#include "Joc.hpp"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "iostream"


void Joc::inicialitza(const string& nomFitxer)
{
    m_partida.inicialitza(nomFitxer);
}

bool Joc::estanAlLado(const Posicio& p1, const Posicio& p2)
{
    int difFila = abs(p1.getFila() - p2.getFila());
    int difColumna = abs(p1.getColumna() - p2.getColumna());

    // Verificar si las posiciones están adyacentes en la dirección horizontal o vertical
    if ((difFila == 1 && difColumna == 0) || (difFila == 0 && difColumna == 1) || (difFila == 0 && difColumna == 0))
    {
        return true;
    }

    return false;
}

void Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime)
{
    Posicio pos1, pos2;

    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);
    m_partida.dibuixa();


    switch (m_estat)
    {
    case ESTAT_JOC_ESPERA:
    {
        if (mouseStatus && (mousePosX <= 550 && mousePosX >= 50) && (mousePosY <= 650 && mousePosY >= 150)) {

            p1.set((mousePosX - CELL_INIT_X) / CELL_W, (mousePosY - CELL_INIT_Y) / CELL_H);
            m_estat = ESTAT_JOC_INTERCANVI;
        }
        else m_estat = ESTAT_JOC_ESPERA;
        break;
    }
    case ESTAT_JOC_INTERCANVI:
    {
        if (mouseStatus && (mousePosX <= 550 && mousePosX >= 50) && (mousePosY <= 650 && mousePosY >= 150)) {

            p2.set((mousePosX - CELL_INIT_X) / CELL_W, (mousePosY - CELL_INIT_Y) / CELL_H);
            if (p1 != p2)
            {
                if (estanAlLado(p1, p2))
                {
                    cout << "Movimiento realizado --> P1: (" << p1.getColumna() << "," << p1.getFila() << ") a P2: (" << p2.getColumna() << "," << p2.getFila() << ")" << endl;
                    
                    resultado = m_partida.iniciaMoviment(p1, p2);
                }
                else
                {
                    cout << "Movimiento No Valido" << endl;
                }

                if (resultado.first != nullptr && resultado.second != 0) 
                {
                    for (int i = 0; i < resultado.second; i++) 
                    {
                        if (m_partida.candy(resultado.first[i]) == BLAU) 
                        {
                            if (m_objectiu > 0) 
                            {
                                m_objectiu--;
                            }
                        }
                    }
                    m_estat = ESTAT_JOC_MOVIMENTS;
                }
            }
            else
                m_estat = ESTAT_JOC_ESPERA;

        }
        else
            m_estat = ESTAT_JOC_ESPERA;
        break;
    }
    case ESTAT_JOC_MOVIMENTS:
    {
        m_temps += deltaTime;
        pos1 = p1;
        pos2 = p2;


        if (m_temps > TEMPS_DESCENS)
        {
            m_partida.continuaMoviment2(pos1, pos2, resultado.first, resultado.second);

            punts += resultado.second * 10; // Incrementar la puntuación en 100 puntos
            counter--;

            if (m_objectiu == 0)
            {
                m_estat = ESTAT_FINAL;
                break;
            }

            m_temps = 0;

            m_estat = ESTAT_JOC_ESPERA; // Cambiar el estado de nuevo a ESTAT_JOC_INTERCANVI o el estado que corresponda después del movimiento
        }
        else
        {
            m_partida.continuaMoviment(pos1, pos2, resultado.first, resultado.second);

            m_estat = ESTAT_JOC_MOVIMENTS;
        }

        break;
    }

    case ESTAT_FINAL:
    {
        string finalMsg = "FINAL";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, FINAL_INIT_X, FINAL_INIT_Y, 1.0, finalMsg);

        if (m_objectiu == 0)
        {
            string guanyat = "HAS GUANYAT!";
            int centerX = SCREEN_SIZE_X / 2 - finalMsg.length() * 10; // Calcular la posición X centrada en la pantalla
            int centerY = SCREEN_SIZE_Y - 50; // Posición Y ajustada para que aparezca en la parte inferior
            GraphicManager::getInstance()->drawFont(FONT_GREEN_30, centerX, centerY, 1.0, guanyat);
        }
        else
        {
            string perdut = "HAS PERDUT!";
            int centerX = SCREEN_SIZE_X / 2 - finalMsg.length() * 10; // Calcular la posición X centrada en la pantalla
            int centerY = SCREEN_SIZE_Y - 50; // Posición Y ajustada para que aparezca en la parte inferior
            GraphicManager::getInstance()->drawFont(FONT_RED_30, centerX, centerY, 1.0, perdut);
        }
        break;
    }
    }

    if (counter == 0)
    {
        m_estat = ESTAT_FINAL;
    }

    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, OBJECTIU_INIT_X, OBJECTIU_INIT_Y, false);

    GraphicManager::getInstance()->drawFont(FONT_RED_30, OBJECTIU_INIT_X - 35, OBJECTIU_INIT_Y, 1, to_string(m_objectiu));



    string counterMsg = "Moviments: " + to_string(counter);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, MOVIMENTS_INIT_X, MOVIMENTS_INIT_Y, 1, counterMsg);

    string puntuacioMsg = "Puntuacio: " + to_string(punts);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, PUNTS_INIT_X, PUNTS_INIT_Y, 1, puntuacioMsg);

}

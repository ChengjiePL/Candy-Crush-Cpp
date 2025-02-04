#include "candy.h"

string Candy::toString() {
    string strTipus;
    switch (m_tipus) {
    case NORMAL:
        strTipus = "Normal";
        break;
    case RATLLAT_HORIZONTAL:
        strTipus = "Ratllat horizontal";
        break;
    case RATLLAT_VERTICAL:
        strTipus = "Ratllat vertical";
        break;
    case BOMBA:
        strTipus = "Bomba";
        break;
    default:
        strTipus = "No tipus";
    }

    string strColor;
    switch (m_color) {
    case VERD:
        strColor = "Verd";
        break;
    case LILA:
        strColor = "Lila";
        break;
    case BLAU:
        strColor = "Blau";
        break;
    case TARONJA:
        strColor = "Taronja";
        break;
    case VERMELL:
        strColor = "Vermell";
        break;
    case GROC:
        strColor = "Groc";
        break;
    default:
        strColor = "No color";
    }
    return strTipus + " " + strColor;
}

void Candy::fromString(string str) {

    if (str == "Normal Verd") {
        m_tipus = NORMAL;
        m_color = VERD;
    }
    else if (str == "Normal Lila") {
        m_tipus = NORMAL;
        m_color = LILA;
    }
    else if (str == "Normal Blau") {
        m_tipus = NORMAL;
        m_color = BLAU;
    }
    else if (str == "Normal Taronja") {
        m_tipus = NORMAL;
        m_color = TARONJA;
    }
    else if (str == "Normal Vermell") {
        m_tipus = NORMAL;
        m_color = VERMELL;
    }
    else if (str == "Normal Groc") {
        m_tipus = NORMAL;
        m_color = GROC;
    }
    else if (str == "Ratllat horizontal Verd") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = VERD;
    }
    else if (str == "Ratllat horizontal Lila") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = LILA;
    }
    else if (str == "Ratllat horizontal Blau") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = BLAU;
    }
    else if (str == "Ratllat horizontal Taronja") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = TARONJA;
    }
    else if (str == "Ratllat horizontal Vermell") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = VERMELL;
    }
    else if (str == "Ratllat horizontal Groc") {
        m_tipus = RATLLAT_HORIZONTAL;
        m_color = GROC;
    }
    else if (str == "Ratllat vertical Verd") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = VERD;
    }
    else if (str == "Ratllat vertical Lila") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = LILA;
    }
    else if (str == "Ratllat vertical Blau") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = BLAU;
    }
    else if (str == "Ratllat vertical Taronja") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = TARONJA;
    }
    else if (str == "Ratllat vertical Vermell") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = VERMELL;
    }
    else if (str == "Ratllat vertical Groc") {
        m_tipus = RATLLAT_VERTICAL;
        m_color = GROC;
    }
    else if (str == "Bomba")
    {
        m_tipus = BOMBA;
    }
    else {
        m_tipus = NO_TIPUS;
        m_color = NO_COLOR;
    }
}

void Candy::dibuixa(int x, int y) 
{
    if (m_tipus == NORMAL)
    {
        if (m_color == BLAU) {                  
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERD) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == LILA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == TARONJA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERMELL) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == GROC) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else {
            return;
        }
    }
    else if (m_tipus == RATLLAT_HORIZONTAL)
    {
        if (m_color == BLAU) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERD) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == LILA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == TARONJA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERMELL) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == GROC) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW_HORIZONTAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else {
            return;
        }
    }
    else if (m_tipus == RATLLAT_VERTICAL)
    {
        if (m_color == BLAU) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERD) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == LILA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == TARONJA) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == VERMELL) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else if (m_color == GROC) {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW_VERTICAL,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
        }
        else {
            return;
        }
    }
    else if (m_tipus == BOMBA)
    {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BOMBA,
                CELL_INIT_X + (x * CELL_W) + (CELL_W / 2),
                CELL_INIT_Y + (y * CELL_H) + (CELL_H / 2), true);
    }
    else
        return;
}
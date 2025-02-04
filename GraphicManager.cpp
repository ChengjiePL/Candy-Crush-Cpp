//
//  GraphicManager.cpp
//  MP_Practica
//
//  Created by Enric Vergara on 13/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#include "GraphicManager.h"
#include <iostream>

GraphicManager* GraphicManager::instance=NULL;

GraphicManager::GraphicManager()
: m_oFontWhite_30(getFontPath(FONT_WHITE_30).c_str(),30,NFont::Color(255,255,255,255))
, m_oFontRed_30(getFontPath(FONT_RED_30).c_str(),30,NFont::Color(255,0,0,255))
, m_oFontGreen_30(getFontPath(FONT_GREEN_30).c_str(),30,NFont::Color(0,255,0,255))
{
    for (int i = 0; i < IMAGE_NUM_MAX; i ++){
        string path = getImagePath((IMAGE_NAME)i);
        m_aSprites[i].create(path.c_str());
    }
}


void GraphicManager::drawSprite (IMAGE_NAME name, float posX, float posY, bool centered) 
{
    if (name >= 0 && name < IMAGE_NUM_MAX)
    {
        if (centered)
        {
            posX -= m_aSprites[name].getScaleX() / 2;
            posY -= m_aSprites[name].getScaleY() / 2;
        }
        m_aSprites[name].draw(posX, posY);
    }
    else
    {
        cout << "Error: no existeix el identificador de image";
    }
    
}

NFont::Rectf GraphicManager::drawFont (FONT_NAME name,
                                       float posX, float posY,
                                       float size,
                                       const string& msg)
{
    switch (name) {
        case FONT_GREEN_30:
            return m_oFontGreen_30.draw(posX, posY, NFont::Scale(size), "%s", msg.c_str());
            break;
        case FONT_RED_30:
            return m_oFontRed_30.draw(posX, posY, NFont::Scale(size), "%s", msg.c_str());
            break;
        case FONT_WHITE_30:
            return m_oFontWhite_30.draw(posX, posY, NFont::Scale(size), "%s", msg.c_str());
            break;
            
        default:
            cout << "Error: no existeix el identificador de font";
            break;
    }
    return NFont::Rectf();
}

string GraphicManager::getImagePath(IMAGE_NAME name){
    string path;
    switch (name) {
        case IMAGE_BACKGROUND:
            path = "data/Graphics/background.png";
            break;
        case IMAGE_BOARD:
            path = "data/Graphics/tauler.png";
            break;
        case IMAGE_PIECE_RED:
			path = "data/Graphics/red.png";
			break;
        case IMAGE_PIECE_RED_VERTICAL:
            path = "data/Graphics/red_vertical.png";
            break;
        case IMAGE_PIECE_RED_HORIZONTAL:
            path = "data/Graphics/red_horizontal.png";
            break;
        case IMAGE_PIECE_ORANGE:
            path = "data/Graphics/orange.png";
            break;
        case IMAGE_PIECE_ORANGE_VERTICAL:
            path = "data/Graphics/orange_vertical.png";
            break;
        case IMAGE_PIECE_ORANGE_HORIZONTAL:
            path = "data/Graphics/orange_horizontal.png";
            break;
        case IMAGE_PIECE_YELLOW:
            path = "data/Graphics/yellow.png";
            break;
        case IMAGE_PIECE_YELLOW_VERTICAL:
            path = "data/Graphics/yellow_vertical.png";
            break;
        case IMAGE_PIECE_YELLOW_HORIZONTAL:
            path = "data/Graphics/yellow_horizontal.png";
            break;
        case IMAGE_PIECE_BLUE:
            path = "data/Graphics/blue.png"; 
            break;
		case IMAGE_PIECE_BLUE_VERTICAL:
			path = "data/Graphics/blue_vertical.png";
			break;
		case IMAGE_PIECE_BLUE_HORIZONTAL:
			path = "data/Graphics/blue_horizontal.png";
			break;
		case IMAGE_PIECE_GREEN:
			path = "data/Graphics/green.png";
			break;
        case IMAGE_PIECE_GREEN_VERTICAL:
            path = "data/Graphics/green_vertical.png";
            break;
        case IMAGE_PIECE_GREEN_HORIZONTAL:
            path = "data/Graphics/green_horizontal.png";
            break;
        case IMAGE_PIECE_PURPLE:
            path = "data/Graphics/purple.png";
            break;
        case IMAGE_PIECE_PURPLE_VERTICAL:
            path = "data/Graphics/purple_vertical.png";
            break;
        case IMAGE_PIECE_PURPLE_HORIZONTAL:
            path = "data/Graphics/purple_horizontal.png";
            break;
        case IMAGE_PIECE_BOMBA:
            path = "data/Graphics/bomba.png";
            break;
        default:
            path = "";
            break;
        
    }
    
    
    
    return path;
}
string GraphicManager::getFontPath(FONT_NAME name){
    string path;
    switch (name) {
        case FONT_GREEN_30:
        case FONT_RED_30:
        case FONT_WHITE_30:
            path = "data/Fonts/FreeSans.ttf";
            break;
            
        default:
            path = "";
            break;
    }
    
    return path;
}


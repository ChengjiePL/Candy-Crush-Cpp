//
//  GraphicManager.hpp
//  MP_Practica
//
//  Created by Enric Vergara on 13/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef GraphicManager_hpp
#define GraphicManager_hpp

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <stdio.h>
#include <string>
#include <map>
using namespace std;


typedef enum {
    IMAGE_BACKGROUND,
    IMAGE_BOARD,
    IMAGE_PIECE_RED,
    IMAGE_PIECE_RED_VERTICAL,
    IMAGE_PIECE_RED_HORIZONTAL,
    IMAGE_PIECE_ORANGE,
    IMAGE_PIECE_ORANGE_VERTICAL,
    IMAGE_PIECE_ORANGE_HORIZONTAL,
    IMAGE_PIECE_YELLOW,
    IMAGE_PIECE_YELLOW_VERTICAL,
    IMAGE_PIECE_YELLOW_HORIZONTAL,
    IMAGE_PIECE_BLUE,
    IMAGE_PIECE_BLUE_VERTICAL,
    IMAGE_PIECE_BLUE_HORIZONTAL,
    IMAGE_PIECE_GREEN,
    IMAGE_PIECE_GREEN_VERTICAL,
    IMAGE_PIECE_GREEN_HORIZONTAL,
    IMAGE_PIECE_PURPLE,
    IMAGE_PIECE_PURPLE_VERTICAL,
    IMAGE_PIECE_PURPLE_HORIZONTAL,
    IMAGE_PIECE_BOMBA,
    IMAGE_NUM_MAX
} IMAGE_NAME;

typedef enum {
    FONT_WHITE_30 = 0,
    FONT_RED_30,
    FONT_GREEN_30,
    
    FONT_NUM_MAX
} FONT_NAME;


class GraphicManager
{
public:
    
    void drawSprite(IMAGE_NAME name, float posX, float posY, bool centered);
    //size: [0-1]
    NFont::Rectf drawFont(FONT_NAME name, float posX,
                                 float posY, float size,
                                 const string& msg);
    
    
    static GraphicManager *getInstance()
    {
        if (instance == NULL)
          instance = new GraphicManager();
        return instance;
    }


    

protected:
    GraphicManager();
    virtual ~GraphicManager() {}
    GraphicManager(GraphicManager const&);
    GraphicManager& operator=(GraphicManager const&);

private:
    static GraphicManager *instance;
    
    Sprite m_aSprites[IMAGE_NUM_MAX];
    NFont m_oFontWhite_30;
    NFont m_oFontRed_30;
    NFont m_oFontGreen_30;
    
private:
    string getImagePath (IMAGE_NAME);
    string getFontPath  (FONT_NAME);
};



#endif /* GraphicManager_hpp */

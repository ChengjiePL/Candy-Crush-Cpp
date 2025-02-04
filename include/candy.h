    #ifndef CANDY_H
    #define CANDY_H

    #include "definicions.h"
    #include "GraphicManager.h"
    #include "InfoJoc.h"

    using namespace std;

    class Candy {
    public:
        Candy() { m_tipus = NO_TIPUS; m_color = NO_COLOR; }
        Candy(const ColorCandy& color, const TipusCandy& tipus) { m_color = color; m_tipus = tipus; }
        ColorCandy getColor() { return m_color; }
        TipusCandy getTipus() { return m_tipus; }
        void setColor(ColorCandy color) { m_color = color; }
        void setTipus(TipusCandy tipus) { m_tipus = tipus; }

        string toString();

        void fromString(string str);

        bool operator==(Candy candy)
        {
            if (candy.getColor() == m_color)
            {
                return true;
            }
            else
                return false;
        }
        bool candyCompatible(const Candy& c) const
        {
            if (m_color != NO_COLOR && m_color == c.m_color)
            {
                return true;
            }
            return false;
        }
        void dibuixa(int x, int y);

    private:
        ColorCandy m_color;
        TipusCandy m_tipus;
    };

    #endif

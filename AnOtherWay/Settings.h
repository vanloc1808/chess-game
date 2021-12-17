#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <SFML/Graphics.hpp>

using namespace sf;

namespace utils {
    class Settings {
    private:
        static Color _blackSquareColor;

        static Color _whiteSquareColor;

        static Color _highlightedColor;

        static Color _checkedColor;

        static float _emptyHighlightedScale;

        static float _occupiedHighlightedScale;

        static float _occupiedHighlightedThickness;

        static float _cellSize;

        static Vector2i _cellOffset; 

    protected:

    public:
        Settings(); //constructor

        ~Settings(); //destructors

        //getters for the above attributess
        static Color getBlackSquareColor();

        static Color getWhiteSquareColor();

        static Color getHighlightedColor();

        static Color getCheckedColor();

        static float getEmptyHighlightedScale();

        static float getOccupiedHighlightedScale();

        static float getOccupiedHighlightedThickness();

        static float getCellSize();

        static Vector2i getCellOffset();

        //settes for some of the above attributes
        static void setBlackSquareColor(const Color& color);

        static void setWhiteSquareColor(const Color& color);

        static void setHighlightedColor(const Color& color);

        static void setEmptyHighlightedScale(const float& scale);

        static void setOccupiedHighlightedScale(const float& scale);

        static void setOccupiedHighlightedThickness(const float& thickness);

        //update cellSize
        static void updateCellSize(const Vector2u& windowSize);

    };
}

#endif //_SETTINGS_H_
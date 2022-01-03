#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <SFML/Graphics.hpp>

using namespace sf;

namespace utilities {
    class Settings {
    private:
        static Color _blackSquareColor; //color of black cells on chess board

        static Color _whiteSquareColor; //color of white cells on chess board

        static Color _highlightedColor; //color of highlighted cell(s) on chess board

        static Color _checkedColor; //color of cell which is the King is situated on if it is checked

        static float _emptyHighlightedScale; //scale of highlighted cells if it is empty

        static float _occupiedHighlightedScale; //scale of highlighted cells if it is occupied

        static float _occupiedHighlightedThickness; //thickness of the highlighter

        static float _cellSize; //size of cell

        static Vector2i _cellOffset; //offset of cell

    protected:

    public:
        Settings(); //constructor

        ~Settings(); //destructors

        //followed are the getters for the above attributes
        static Color getBlackSquareColor(); //getter for color of black cells

        static Color getWhiteSquareColor(); //getter for color of white cells

        static Color getHighlightedColor(); //get for color of highlighted cell(s)

        static Color getCheckedColor(); //getter for color of checked position

        static float getEmptyHighlightedScale(); //getter for scale of highlighted cells if it is empty

        static float getOccupiedHighlightedScale(); //getter for scale of highlighted cells if it is occupied

        static float getOccupiedHighlightedThickness(); //getter for thickness of the highlighter

        static float getCellSize(); //getter for size of cell

        static Vector2i getCellOffset(); //getter for offset of cell

        //followed are the setters for some of the above attributes
        //the following four are setters for color, if necessary
        static void setBlackSquareColor(const Color& color); //setter for color of black cells

        static void setWhiteSquareColor(const Color& color); //setter for color of white cells

        static void setHighlightedColor(const Color& color); //setter for color of highlighted cell(s)

        static void setCheckedColor(const Color& color); //setter for color of checked position

        //the following two are setters for scale
        static void setEmptyHighlightedScale(const float& scale); //setter for scale of highlighted cells if it is empty

        static void setOccupiedHighlightedScale(const float& scale); //setter for scale of highlighted cells if it is occupied

        static void setOccupiedHighlightedThickness(const float& thickness); //setter for thickness of the highlighter

        //update cellSize
        static void updateCellSize(const Vector2u& windowSize);

    };
}

#endif //_SETTINGS_H_
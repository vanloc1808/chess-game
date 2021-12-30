#include "Settings.h"

namespace utilities {
    //set the default value for static attributes
    Color Settings::_blackSquareColor = Color(119, 120, 122);
    Color Settings::_whiteSquareColor = Color(244, 244, 211);
    Color Settings::_highlightedColor = Color(50, 50, 50, 60);
    Color Settings::_checkedColor = Color(255, 0, 0);

    float Settings::_emptyHighlightedScale = 0.3;
    float Settings::_occupiedHighlightedScale = 0.7;
    float Settings::_occupiedHighlightedThickness = 12;

    float Settings::_cellSize = 0;
    Vector2i Settings::_cellOffset = Vector2i(0, 0);  
    Settings::Settings() {
        //do nothing
    }  

    Settings::~Settings() {
        //do nothing
    }

    Color Settings::getBlackSquareColor() {
        return Settings::_blackSquareColor;
    }

    Color Settings::getWhiteSquareColor() {
        return Settings::_whiteSquareColor;
    }

    Color Settings::getHighlightedColor() {
        return Settings::_highlightedColor;
    }

    Color Settings::getCheckedColor() {
        return Settings::_checkedColor;
    }

    float Settings::getEmptyHighlightedScale() {
        return Settings::_emptyHighlightedScale;
    }

    float Settings::getOccupiedHighlightedScale() {
        return Settings::_occupiedHighlightedScale;
    }

    float Settings::getOccupiedHighlightedThickness() {
        return Settings::_occupiedHighlightedThickness;
    }

    float Settings::getCellSize() {
        if (Settings::_cellSize == 0) {
            throw std::runtime_error (
                "The size of cell has not been initilized yet"
            );
        }

        return Settings::_cellSize;
    }

    Vector2i Settings::getCellOffset() {
        return Settings::_cellOffset;
    }

    void Settings::setBlackSquareColor(const Color& color) {
        Settings::_blackSquareColor = color;
    }

    void Settings::setWhiteSquareColor(const Color& color) {
        Settings::_whiteSquareColor = color;
    }

    void Settings::setHighlightedColor(const Color& color) {
        Settings::_highlightedColor = color;
    }

    void Settings::setEmptyHighlightedScale(const float& scale) {
        Settings::_emptyHighlightedScale = scale;
    }

    void Settings::setOccupiedHighlightedScale(const float& scale) {
        Settings::_occupiedHighlightedScale = scale;
    }

    void Settings::setOccupiedHighlightedThickness(const float& thickness) {
        Settings::_occupiedHighlightedThickness = thickness;
    }

    void Settings::updateCellSize(const Vector2u& windowSize) {
        if (windowSize.x <= 0 || windowSize.y <= 0) {
            throw std::runtime_error (
                "Invalid paramter"
            );
        }

        Settings::_cellSize = std::min(windowSize.x, windowSize.y) / 8;

        Settings::_cellOffset.x = (windowSize.x - Settings::_cellSize * 8) / 2;
        Settings::_cellOffset.y = (windowSize.y - Settings::_cellSize * 8) / 2;
    }
}
#include "Cell.h"

using namespace utilities;

bool Cell::getIsChecked() {
    return this->_isChecked;
}

void Cell::highlight(bool highlightCell) {
    if (highlightCell == true) {
        this->_status = CellStatus::HIGHLIGHTED;

        if (this->_piece == nullptr) {
            //empty cell
            this->_highlightedCircle.setFillColor(Settings::getHighlightedColor());

            this->_highlightedCircle.setOutlineThickness(0);

            this->_highlightedCircle.setScale(Settings::getEmptyHighlightedScale(), Settings::getEmptyHighlightedScale());        
        } else {
            //occupied cell
            this->_highlightedCircle.setFillColor(Color(0, 0, 0, 0));

            this->_highlightedCircle.setOutlineThickness(Settings::getOccupiedHighlightedThickness());

            this->_highlightedCircle.setScale(Settings::getOccupiedHighlightedScale(), Settings::getOccupiedHighlightedScale());
        }
    } else {
        if (this->_piece == nullptr) {
            this->_status = CellStatus::EMPTY;
        } else {
            this->_status = CellStatus::OCCUPIED;
        }
    }
}

void Cell::setIsChecked(bool check) {
    this->_isChecked = check;
}
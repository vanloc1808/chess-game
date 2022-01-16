#include "Cell.h"

using namespace utilities;

//default constructor, no need to do anything
Cell::Cell() {

}

//destructor, no need to do anything
Cell::~Cell() {

}

bool Cell::getIsChecked() {
    return this->_isChecked;
}

void Cell::highlight(bool highlightCell) {
    //if the highlightCell == true, therefore we need to highlight this cell
    if (highlightCell == true) {
        this->_status = CellStatus::HIGHLIGHTED;

        //document for Shape classes of SFML here:
        //https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php
        if (this->_piece == nullptr) {
            //if there is no pieces on this cell, aka the cell is empty
            this->_highlightedCircle.setFillColor(Settings::getHighlightedColor());

            this->_highlightedCircle.setOutlineThickness(0);

            this->_highlightedCircle.setScale(Settings::getEmptyHighlightedScale(), Settings::getEmptyHighlightedScale());        
        } else {
            //if there is a piece on this cell, aka the cell is occupied
            this->_highlightedCircle.setFillColor(Color(0, 0, 0, 0));

            this->_highlightedCircle.setOutlineThickness(Settings::getOccupiedHighlightedThickness());

            this->_highlightedCircle.setScale(Settings::getOccupiedHighlightedScale(), Settings::getOccupiedHighlightedScale());
        }
    //if the highlightedCell == false, we don't need to highlight this cell
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
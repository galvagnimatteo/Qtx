#include "rawcut.h"

RawCut::RawCut(unsigned int fabric_height, unsigned int n_pieces) : fabric_height(fabric_height), n_pieces(n_pieces) { }

const unsigned int RawCut::MIN_FABRIC_HEIGHT = 90;
const unsigned int RawCut::MAX_FABRIC_HEIGHT = 300;

const unsigned int RawCut::MIN_PIECES = 100;
const unsigned int RawCut::MAX_PIECES = 5000;

unsigned int RawCut::getFabricHeight() const {
    return fabric_height;
}

unsigned int RawCut::getPiecesNumber() const {
    return n_pieces;
}

void RawCut::setFabricHeight(unsigned int fh){
    fabric_height = fh;
}

void RawCut::setPiecesNumber(unsigned int pn){
    n_pieces = pn;
}

std::string RawCut::toString() const{

    return "Altezza tessuto: " + std::to_string(getFabricHeight()) + "cm\nNumero pezzi: " + std::to_string(getPiecesNumber()) + "\n";

}

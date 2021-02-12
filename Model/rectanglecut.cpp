#include "rectanglecut.h"

RectangleCut::RectangleCut(unsigned int fabric_height, unsigned int n_pieces, unsigned int piece_height, unsigned int piece_lenght)
    : RawCut(fabric_height, n_pieces), piece_height(piece_height), piece_lenght(piece_lenght) { }

unsigned int RectangleCut::getPieceLenght() const {
    return piece_lenght;
}

unsigned int RectangleCut::getPieceHeight() const {
    return piece_height;
}

void RectangleCut::setPieceLenght(unsigned int pl){
    piece_lenght = pl;
}

void RectangleCut::setPieceHeight(unsigned int ph){
    piece_height = ph;
}

RectangleCut* RectangleCut::clone() const{
  return new RectangleCut(*this);
}

unsigned int RectangleCut::getConsumption() const {

    unsigned int n_column = getFabricHeight() / piece_height;
    unsigned int consumption = 0;
    unsigned int n_done = 0;

    while(n_done < getPiecesNumber()){

        consumption += piece_lenght;
        n_done += n_column;

    }

    return roundeven(consumption);

}

std::string RectangleCut::toString() const{

    return RawCut::toString() + "Misure pezzo: " + std::to_string(getPieceLenght()) + "cm X " + std::to_string(getPieceHeight()) + "cm\n";

}

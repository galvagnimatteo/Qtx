#include "obliquecut.h"

ObliqueCut::ObliqueCut(unsigned int fabric_height, unsigned int n_pieces, unsigned int piece_lenght, unsigned int piece_height, unsigned int angle)
    : RectangleCut(fabric_height, n_pieces, piece_lenght, piece_height), angle(angle) { }

unsigned int ObliqueCut::getAngle() const{
    return angle;
}

void ObliqueCut::setAngle(unsigned int a){
    angle = a;
}

ObliqueCut* ObliqueCut::clone() const{
  return new ObliqueCut(*this);
}

unsigned int ObliqueCut::getPiecesPerDiagonal(unsigned int fabric_height, unsigned int piece_height, unsigned int piece_lenght, unsigned int angle){

    unsigned int diag = fabric_height / sin(angle * M_PI/180);
    unsigned int n_diag = round((diag - sqrt(pow(piece_lenght / sin(angle * M_PI/180), 2) - pow(piece_lenght, 2))) /piece_height);
    return n_diag;

}

unsigned int ObliqueCut::getConsumption() const {

    unsigned int n_done = 0;
    unsigned int diag = getFabricHeight() / sin(angle * M_PI/180);
    unsigned int n_diag = getPiecesPerDiagonal(getFabricHeight(), getPieceHeight(), getPieceLenght(), angle);
    unsigned int consumption = 0;

    consumption += diag / sin(angle * M_PI/180);

    while(n_done < getPiecesNumber()){

        consumption += getPieceLenght() / sin(angle * M_PI/180);
        n_done += n_diag;

    }

    return roundeven(consumption);

}

std::string ObliqueCut::toString() const{

    return RectangleCut::toString() + "Inclinazione: " + std::to_string(getAngle());

}

#include "collarcut.h"

CollarCut::CollarCut(unsigned int fabric_height, unsigned int n_pieces, unsigned int collar_width, unsigned int collar_radius, unsigned int waste)
    : RectangleCut(fabric_height, n_pieces, CollarCut::computePieceLenght(collar_width, collar_radius, waste), CollarCut::computePieceHeight(collar_width, collar_radius)),
      collar_width(collar_width), collar_radius(collar_radius), waste(waste) { }

const unsigned int CollarCut::MAX_COLLAR_WIDTH = 5;
const unsigned int CollarCut::MAX_COLLAR_RADIUS = 30;

const unsigned int CollarCut::MIN_COLLAR_RADIUS = 10;
const unsigned int CollarCut::MIN_COLLAR_WIDTH = 1;

unsigned int CollarCut::computePieceLenght(unsigned int c_width, unsigned int c_radius, unsigned int w){
    return w + c_radius + (c_width * 2);
}

unsigned int CollarCut::computePieceHeight(unsigned int c_width, unsigned int c_radius){
    return c_radius + c_width;
}

unsigned int CollarCut::getCollarWidth() const {
  return collar_width;
}

unsigned int CollarCut::getCollarRadius() const {
  return collar_radius;
}

unsigned int CollarCut::getWaste() const{
    return waste;
}

void CollarCut::setCollarWidth(unsigned int cw){
    collar_width = cw;
}

void CollarCut::setCollarRadius(unsigned int cr){
    collar_radius = cr;
}

void CollarCut::setWaste(unsigned int w){
    waste = w;
}

CollarCut* CollarCut::clone() const{
  return new CollarCut(*this);
}

std::string CollarCut::toString() const{

    return RectangleCut::toString() + "Larghezza colletti: " + std::to_string(getCollarWidth()) + "cm, Raggio colletti: " + std::to_string(getCollarRadius()) + "cm, Scarto: " + std::to_string(getWaste()) + "cm\n";

}


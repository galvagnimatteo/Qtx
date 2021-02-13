#ifndef COLLARCUT_H
#define COLLARCUT_H

#include "Model/rectanglecut.h"

class CollarCut: public RectangleCut {

private:

    unsigned int collar_width;
    unsigned int collar_radius;
    unsigned int waste;

public:

    static const unsigned int MAX_COLLAR_WIDTH;
    static const unsigned int MAX_COLLAR_RADIUS;

    static const unsigned int MIN_COLLAR_RADIUS;
    static const unsigned int MIN_COLLAR_WIDTH;

    static const unsigned int MIN_COLLAR_WASTE;

    CollarCut(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

    static unsigned int computePieceLenght(unsigned int, unsigned int, unsigned int);
    static unsigned int computePieceHeight(unsigned int, unsigned int);

    unsigned int getCollarWidth() const;
    unsigned int getCollarRadius() const;
    unsigned int getWaste() const;
    void setCollarWidth(unsigned int);
    void setCollarRadius(unsigned int);
    void setWaste(unsigned int);

    std::string toString() const override;

    CollarCut* clone() const override;

};

#endif

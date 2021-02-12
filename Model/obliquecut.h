#ifndef OBLIQUECUT_H
#define OBLIQUECUT_H

#include "Model/rectanglecut.h"
#include <cmath>

class ObliqueCut: public RectangleCut{

private:

    unsigned int angle; 

public:

    ObliqueCut(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

    unsigned int getConsumption() const override;
    unsigned int getAngle() const;
    void setAngle(unsigned int);

    std::string toString() const override;

    ObliqueCut* clone() const override;

    static unsigned int getPiecesPerDiagonal(unsigned int, unsigned int, unsigned int, unsigned int);

};

#endif

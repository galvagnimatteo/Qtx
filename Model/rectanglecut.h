#ifndef RECTANGLECUT_H
#define RECTANGLECUT_H

#include <Model/rawcut.h>
#include <math.h>

class RectangleCut: public RawCut{

private:

    unsigned int piece_height;
    unsigned int piece_lenght;

public:

    RectangleCut(unsigned int, unsigned int, unsigned int, unsigned int);

    unsigned int getPieceHeight() const;
    unsigned int getPieceLenght() const;
    void setPieceHeight(unsigned int);
    void setPieceLenght(unsigned int);

    std::string toString() const override;
    unsigned int getConsumption() const override;

    RectangleCut* clone() const override;

};

#endif

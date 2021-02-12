#ifndef RAWCUT_H
#define RAWCUT_H

#include <QListWidgetItem>

class RawCut{

private:

    unsigned int fabric_height;
    unsigned int n_pieces;

public:

    static const unsigned int MIN_FABRIC_HEIGHT;
    static const unsigned int MAX_FABRIC_HEIGHT;

    static const unsigned int MIN_PIECES;
    static const unsigned int MAX_PIECES;

    RawCut(unsigned int, unsigned int);
    virtual ~RawCut() = default;

    virtual unsigned int getConsumption() const = 0;
    unsigned int getFabricHeight() const;
    unsigned int getPiecesNumber() const;
    void setFabricHeight(unsigned int);
    void setPiecesNumber(unsigned int);

    virtual std::string toString() const;

    virtual RawCut* clone() const = 0;

};

#endif

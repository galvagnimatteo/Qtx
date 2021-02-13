#include "mainmodel.h"
#include "rectanglecut.h"

MainModel::MainModel(QObject *parent): QObject(parent){

    this->cuts_list = new C<DeepPtr<RawCut>>();

}

void MainModel::insert(const DeepPtr<RawCut> &rc){

    cuts_list->append(rc);

    emit modelUpdated();

}

const DeepPtr<RawCut> MainModel::getCutByIndex(int index) const{

    auto it = cuts_list->begin();

    for(int counter = 0; counter < index; counter++){

        ++it;

    }

    return *it;

}

void MainModel::modifyRectangleCut(int index, unsigned int fabric_height, unsigned int n_pieces, unsigned int piece_height, unsigned int piece_width){

    RectangleCut* rc;

    auto it = cuts_list->begin();

    for(int counter = 0; counter < index; counter++){

        ++it;

    }

    rc = dynamic_cast<RectangleCut*> (&*it); //indirizzo di **it che è rawcut (rectanglecut dinamicamente) perchè *it è deepptr<rawcut>

    rc->setFabricHeight(fabric_height);
    rc->setPieceHeight(piece_height);
    rc->setPieceLenght(piece_width);
    rc->setPiecesNumber(n_pieces);

    emit modelUpdated();

}

void MainModel::modifyObliqueCut(int index, unsigned int fabric_height, unsigned int n_pieces, unsigned int piece_height, unsigned int piece_width, unsigned int angle){

    ObliqueCut* oc;

    auto it = cuts_list->begin();

    for(int counter = 0; counter < index; counter++){

        ++it;

    }

    oc = dynamic_cast<ObliqueCut*> (&*it);

    oc->setFabricHeight(fabric_height);
    oc->setPieceHeight(piece_height);
    oc->setPieceLenght(piece_width);
    oc->setPiecesNumber(n_pieces);
    oc->setAngle(angle);

    emit modelUpdated();

}

void MainModel::modifyCollarCut(int index, unsigned int fabric_height, unsigned int n_pieces, unsigned int collar_width, unsigned int collar_radius, unsigned int collar_waste){

    CollarCut* cc;

    auto it = cuts_list->begin();

    for(int counter = 0; counter < index; counter++){

        ++it;

    }

    cc = dynamic_cast<CollarCut*> (&*it);

    cc->setFabricHeight(fabric_height);
    cc->setPiecesNumber(n_pieces);
    cc->setCollarWidth(collar_width);
    cc->setCollarRadius(collar_radius);
    cc->setWaste(collar_waste);

    cc->setPieceLenght(CollarCut::computePieceLenght(collar_width, collar_radius, collar_waste));
    cc->setPieceHeight(CollarCut::computePieceHeight(collar_width, collar_radius));

    emit modelUpdated();

}

C<DeepPtr<RawCut>> MainModel::getAllCuts() const{

    return *cuts_list;

}

void MainModel::removeByIndex(int index){

    cuts_list->remove(index);

    emit modelUpdated();

}

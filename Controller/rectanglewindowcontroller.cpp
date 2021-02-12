#include "Controller/rectanglewindowcontroller.h"
#include "View/rectanglewindow.h"

#include <iostream>
RectangleWindowController::RectangleWindowController(View* v, MainModel* m) : Controller(v, m){ }

void RectangleWindowController::openObliqueLayout(int index) const{

    ObliqueView* ol = new ObliqueView(getView());

    View::connectViewController(ol, getModel());

    dynamic_cast<RectangleWindow*>(Controller::getView())->changeLayout(ol); //uso la getView di Controller per ottenere la View* collegata e di questa faccio il dynamic_cast a RectangleWindow.

    if(index >= 0) ol->getController()->updateFields(index); //updatefields solo se la view ha un'indice valido relativo alla lista, ovvero aperta in "modifica"

}

void RectangleWindowController::openRectangleLayout(int index) const{

    RectangleView* rl = new RectangleView(getView());

    View::connectViewController(rl, getModel()); //crea e collega controller a view

    dynamic_cast<RectangleWindow*>(Controller::getView())->changeLayout(rl);

    if(index >= 0) rl->getController()->updateFields(index);

}

void RectangleWindowController::openCollarLayout(int index) const{

    CollarView* cl = new CollarView(getView());

    View::connectViewController(cl, getModel()); //crea e collega controller a view

    dynamic_cast<RectangleWindow*>(Controller::getView())->changeLayout(cl);

    if(index >= 0) cl->getController()->updateFields(index);

}

void RectangleWindowController::emitLockViewSignal(){

    emit lockViewSignal();

}

void RectangleWindowController::emitUnlockViewSignal(){

    emit unlockViewSignal();

}

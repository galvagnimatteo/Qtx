#include "Controller/rectanglewindowcontroller.h"
#include "View/rectanglewindow.h"

RectangleWindowController::RectangleWindowController(View* v, MainModel* m) : Controller(v, m){ }

void RectangleWindowController::openObliqueLayout(int index){

    ObliqueView* ol = new ObliqueView(getView());

    View::connectViewController(ol, getModel());

    emit changeLayoutSignal(ol);

    if(index >= 0) ol->getController()->updateFields(index); //updatefields solo se la view ha un'indice valido (non negativo) relativo alla lista, ovvero aperta in "modifica"

}

void RectangleWindowController::openRectangleLayout(int index){

    RectangleView* rl = new RectangleView(getView());

    View::connectViewController(rl, getModel()); //crea e collega controller a view

    emit changeLayoutSignal(rl);

    if(index >= 0) rl->getController()->updateFields(index);

}

void RectangleWindowController::openCollarLayout(int index){

    CollarView* cl = new CollarView(getView());

    View::connectViewController(cl, getModel()); //crea e collega controller a view

    emit changeLayoutSignal(cl); //gestito da rectanglewindow che cambierà il widget

    if(index >= 0) cl->getController()->updateFields(index);

}

void RectangleWindowController::emitLockViewSignal(){

    emit lockViewSignal();

}

void RectangleWindowController::emitUnlockViewSignal(){

    emit unlockViewSignal();

}

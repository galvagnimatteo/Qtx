#include "Controller/maincontroller.h"
#include "View/rectanglewindow.h"
#include "Controller/rectanglewindowcontroller.h"

#include <QMessageBox>

MainController::MainController(View* v, MainModel* m) : Controller(v, m){

    connect(getModel(), SIGNAL(modelUpdated()), getView(), SLOT(updateView())); //quando il controller riceve il segnale modelupdated chiama lo slot relativo nella view

}

void MainController::openRectangleWindow(){

    RectangleWindow* rw = new RectangleWindow();

    View::connectViewController(rw, this->getModel()); //crea e collega controller a view

    connect(rw->getController(), SIGNAL(lockViewSignal()), this->getView(), SLOT(lockView()));
    connect(rw->getController(), SIGNAL(unlockViewSignal()), this->getView(), SLOT(unlockView()));

    rw->getController()->openRectangleLayout(); //aperto rectangle layout di default
    //openRectangleLayout chiamato qui perchè il RectangleWindowController è definito solo dopo connectViewController

    rw->setRectangleButtonSelected();

    rw->show();

}

void MainController::openModifyView(int index){

    if(index == -1){

        QMessageBox::critical(getView(), "Errore!", "Nessun taglio selezionato.");

    }else{

        const DeepPtr<RawCut> cut = getModel()->getCutByIndex(index);

        if(dynamic_cast<const RectangleCut*>(&*cut)){

            RectangleWindow* rw = new RectangleWindow();

            View::connectViewController(rw, this->getModel());

            connect(rw->getController(), SIGNAL(lockViewSignal()), this->getView(), SLOT(lockView()));
            connect(rw->getController(), SIGNAL(unlockViewSignal()), this->getView(), SLOT(unlockView()));

            if(dynamic_cast<const CollarCut*>(&*cut)){ //tipo dinamico collarcut

                rw->getController()->openCollarLayout(index);
                rw->setCollarButtonSelected();

            }else if(dynamic_cast<const ObliqueCut*>(&*cut)){ //tipo dinamico obliquecut

                rw->getController()->openObliqueLayout(index);
                rw->setObliqueButtonSelected();

            }else{

                rw->getController()->openRectangleLayout(index); //tipo dinamico rectanglecut
                rw->setRectangleButtonSelected();

            }

            rw->disableRadioGroup();
            rw->show();

        }

    }

}

void MainController::deleteSelectedCut(int index){

    if(index == -1){

        QMessageBox::critical(getView(), "Errore!", "Nessun taglio selezionato.");

    }else{

        getModel()->removeByIndex(index);

    }

}

C<DeepPtr<RawCut>> MainController::getAllCuts() const{

    return getModel()->getAllCuts();

}

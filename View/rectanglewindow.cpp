#include "rectanglewindow.h"
#include "Controller/rectanglecontroller.h"
#include "Controller/obliquecontroller.h"
#include "Controller/collarcontroller.h"

RectangleWindow::RectangleWindow(QWidget *parent) : View(parent){ //APPUNTI: override metodo show per mandare il segnale?

    setAttribute(Qt::WA_DeleteOnClose);

    mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignLeft);
    addButtons(mainLayout);

    mainLayout->setContentsMargins(20, 0, 20, 20);

    setLayout(mainLayout);

}

void RectangleWindow::closeEvent(QCloseEvent *event){

    //sblocca mainview
    emit unlockViewSignal();

    event->accept();

}

void RectangleWindow::showEvent(QShowEvent *event){

    //blocca mainview
    emit lockViewSignal();

    event->accept();

}

void RectangleWindow::addButtons(QHBoxLayout* layout) {

    buttonsLayout = new QVBoxLayout;

    groupBox = new QGroupBox();
    rectangle = new QRadioButton("Rettangolo");
    oblique = new QRadioButton("Obliquo");
    collar = new QRadioButton("Colletto");

    buttonsLayout->addWidget(rectangle);
    buttonsLayout->addWidget(oblique);
    buttonsLayout->addWidget(collar);

    groupBox->setLayout(buttonsLayout);
    groupBox->setContentsMargins(10, 20, 0, 0);
    groupBox->setFixedWidth(200);
    groupBox->setFixedHeight(280);

    layout->addWidget(groupBox);

}

RectangleWindowController* RectangleWindow::createController(MainModel* m){

    RectangleWindowController* rwc = new RectangleWindowController(this, m);

    connect(rectangle, SIGNAL(clicked(bool)), rwc, SLOT(openRectangleLayout()));
    connect(oblique, SIGNAL(clicked(bool)), rwc, SLOT(openObliqueLayout()));
    connect(collar, SIGNAL(clicked(bool)), rwc, SLOT(openCollarLayout()));

    connect(this, SIGNAL(lockViewSignal()), rwc, SLOT(emitLockViewSignal()));
    connect(this, SIGNAL(unlockViewSignal()), rwc, SLOT(emitUnlockViewSignal()));

    return rwc;

}

RectangleWindowController* RectangleWindow::getController() const{

    return dynamic_cast<RectangleWindowController*> (View::getController()); //uso il getcontroller di view

}

//Riceve un view* ed essendo "figlio" di widget* può essere aggiunto al layout con addwidget.
void RectangleWindow::changeLayout(View* b){

    QLayoutItem *item;

    if((item = mainLayout->takeAt(1)) != nullptr){

        delete item->widget(); //elimina chiamando il distruttore del widget (~RectangleView, ...)
        delete item;

    }

    mainLayout->addWidget(b); //il widget che vado ad aggiungere in posizione 1 è comunque View*

    adjustSize();
    setFixedSize(size()); //fisso la grandezza della finestra

}

void RectangleWindow::setRectangleButtonSelected(){

    rectangle->setChecked(true);

}

void RectangleWindow::setCollarButtonSelected(){

    collar->setChecked(true);

}

void RectangleWindow::setObliqueButtonSelected(){

    oblique->setChecked(true);

}

void RectangleWindow::disableRadioGroup(){

    groupBox->setDisabled(true);

}

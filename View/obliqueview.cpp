#include "obliqueview.h"

#include <QDoubleValidator>
#include <QIntValidator>

ObliqueView::ObliqueView(QWidget *parent) : View(parent){

    mainlayout = new QHBoxLayout();
    groupboxlayout = new QVBoxLayout();
    rectanglecutlayout = new QVBoxLayout();
    obliquecutlayout = new QVBoxLayout();
    calcolate = new QPushButton("Calcola");

    fabric_height = new QLineEdit();
    n_pieces = new QLineEdit();
    piece_height = new QLineEdit();
    piece_lenght = new QLineEdit();
    calcolate = new QPushButton("Calcola");

    fabric_height->setPlaceholderText("Altezza tessuto");
    n_pieces->setPlaceholderText("Numero pezzi");
    piece_height->setPlaceholderText("Altezza pezzo");
    piece_lenght->setPlaceholderText("Larghezza pezzo");

    fabric_height->setFixedWidth(200);
    n_pieces->setFixedWidth(200);
    piece_height->setFixedWidth(200);
    piece_lenght->setFixedWidth(200);

    fabric_height->setValidator(new QIntValidator(RawCut::MIN_FABRIC_HEIGHT, RawCut::MAX_FABRIC_HEIGHT, mainlayout));
    n_pieces->setValidator(new QIntValidator(RawCut::MIN_PIECES, RawCut::MAX_PIECES, mainlayout));
    piece_lenght->setValidator(new QIntValidator(0, 99, mainlayout));
    piece_height->setValidator(new QIntValidator(0, 99, mainlayout));

    rectanglecutlayout->addWidget(fabric_height);
    rectanglecutlayout->addWidget(n_pieces);
    rectanglecutlayout->addWidget(piece_height);
    rectanglecutlayout->addWidget(piece_lenght);

    //checkbox con i gradi di inclinazione

    groupBox = new QGroupBox();
    degrees30 = new QRadioButton("30 gradi");
    degrees45 = new QRadioButton("45 gradi");
    degrees60 = new QRadioButton("60 gradi");

    groupboxlayout->addWidget(degrees30);
    groupboxlayout->addWidget(degrees45);
    groupboxlayout->addWidget(degrees60);

    groupBox->setLayout(groupboxlayout);
    groupBox->setFixedHeight(185);

    obliquecutlayout->addWidget(groupBox);
    obliquecutlayout->addWidget(calcolate);
    obliquecutlayout->setContentsMargins(20, 0, 0, 0);
    obliquecutlayout->setSpacing(20);

    mainlayout->addLayout(rectanglecutlayout);
    mainlayout->addLayout(obliquecutlayout);

    connect(calcolate, SIGNAL(clicked(bool)), this, SLOT(addOrModifyObliqueCut()));

    index = -1;

    this->setContentsMargins(20, 20, 0, 0);
    this->setLayout(mainlayout);

}

ObliqueController* ObliqueView::createController(MainModel* m){

    return new ObliqueController(this, m);

}

ObliqueController* ObliqueView::getController() const{

    return dynamic_cast<ObliqueController*> (View::getController()); //uso il getcontroller di view

}

void ObliqueView::addOrModifyObliqueCut(){


    unsigned int angle = 0;

    if(degrees30->isChecked()){

        angle = 30;

    }else if(degrees45->isChecked()){

        angle = 45;

    }else if(degrees60->isChecked()){

        angle = 60;

    }

    if(calcolate->text() == QString::fromStdString("Modifica")){

        emit modifyObliqueCutSignal(index, fabric_height->text(), n_pieces->text(), piece_height->text(), piece_lenght->text(), angle);

    }else{

        emit addObliqueCutSignal(fabric_height->text(), n_pieces->text(), piece_height->text(), piece_lenght->text(), angle);

    }

}

void ObliqueView::updateFields(int list_index){

    const DeepPtr<ObliqueCut> oc = getController()->getCutByIndex(list_index);

    fabric_height->setText(QString::number(oc->getFabricHeight()));
    n_pieces->setText(QString::number(oc->getPiecesNumber()));
    piece_height->setText(QString::number(oc->getPieceHeight()));
    piece_lenght->setText(QString::number(oc->getPieceLenght()));

    if(oc->getAngle() == 30){

        degrees30->setChecked(true);

    }else if(oc->getAngle() == 45){

        degrees45->setChecked(true);

    }else{ //sono sicuro sia 60 perchè se no sarebbe stato fermato dal controllo in inserimento

        degrees60->setChecked(true);

    }

    calcolate->setText("Modifica");

    index = list_index;

}

#include "collarview.h"
#include <QIntValidator>
#include <QDoubleValidator>

CollarView::CollarView(QWidget *parent) : View(parent){

    mainlayout = new QHBoxLayout();
    rectanglecutlayout = new QVBoxLayout();
    collarcutlayout = new QVBoxLayout();
    calcolate = new QPushButton("Calcola");

    fabric_height = new QLineEdit();
    n_pieces = new QLineEdit();
    piece_height = new QLineEdit();
    piece_lenght = new QLineEdit();

    collar_width = new QLineEdit();
    collar_radius = new QLineEdit();
    collar_waste = new QLineEdit();

    calcolate = new QPushButton("Calcola");

    fabric_height->setPlaceholderText("Altezza tessuto");
    n_pieces->setPlaceholderText("Numero pezzi");

    piece_height->setText("Altezza pezzo: ");
    piece_lenght->setText("Larghezza pezzo: ");
    piece_height->setDisabled(true);
    piece_lenght->setDisabled(true);

    collar_radius->setPlaceholderText("Raggio colletto");
    collar_width->setPlaceholderText("Larghezza colletto");
    collar_waste->setPlaceholderText("Scarto");

    piece_height->setStyleSheet("color: black;  background-color: lightgrey");
    piece_lenght->setStyleSheet("color: black;  background-color: lightgrey");

    fabric_height->setFixedWidth(200);
    n_pieces->setFixedWidth(200);
    piece_height->setFixedWidth(200);
    piece_lenght->setFixedWidth(200);

    collar_width->setFixedWidth(200);
    collar_radius->setFixedWidth(200);
    collar_waste->setFixedWidth(200);

    fabric_height->setValidator(new QIntValidator(RawCut::MIN_FABRIC_HEIGHT, RawCut::MAX_FABRIC_HEIGHT, mainlayout));
    n_pieces->setValidator(new QIntValidator(RawCut::MIN_PIECES, RawCut::MAX_PIECES, mainlayout));

    collar_width->setValidator(new QIntValidator(0, 9, mainlayout));
    collar_radius->setValidator(new QIntValidator(0, 99, mainlayout));
    collar_waste->setValidator(new QIntValidator(0, 9, mainlayout));

    rectanglecutlayout->addWidget(fabric_height);
    rectanglecutlayout->addWidget(n_pieces);
    rectanglecutlayout->addWidget(piece_height);
    rectanglecutlayout->addWidget(piece_lenght);

    collarcutlayout->addWidget(collar_width);
    collarcutlayout->addWidget(collar_radius);
    collarcutlayout->addWidget(collar_waste);
    collarcutlayout->addWidget(calcolate);

    collarcutlayout->setContentsMargins(20, 0, 0, 0);

    mainlayout->addLayout(rectanglecutlayout);
    mainlayout->addLayout(collarcutlayout);

    connect(calcolate, SIGNAL(clicked(bool)), this, SLOT(addOrModifyCollarCut()));

    index = -1;

    this->setContentsMargins(20, 20, 0, 0);
    this->setLayout(mainlayout);

}

CollarController* CollarView::createController(MainModel* m){

    return new CollarController(this, m);

}

CollarController* CollarView::getController() const{

    return dynamic_cast<CollarController*> (View::getController()); //uso il getcontroller di view

}

void CollarView::addOrModifyCollarCut(){

    if(calcolate->text() == QString::fromStdString("Modifica")){

        getController()->modifyCollarCut(index, fabric_height->text(), n_pieces->text(), collar_width->text(), collar_radius->text(), collar_waste->text());

    }else{

        getController()->addCollarCut(fabric_height->text(), n_pieces->text(), collar_width->text(), collar_radius->text(), collar_waste->text()); //emette il segnale per il controller, utile per passare parametri al controller

    }

}

void CollarView::updatePieceMeasures(unsigned int piece_height, unsigned int piece_lenght){

    this->piece_height->setText("Altezza pezzo: " + QString::number(piece_height));
    this->piece_lenght->setText("Larghezza pezzo: " + QString::number(piece_lenght));

}

void CollarView::updateFields(int list_index){

    const DeepPtr<CollarCut> cv = getController()->getCutByIndex(list_index);

    fabric_height->setText(QString::number(cv->getFabricHeight()));
    n_pieces->setText(QString::number(cv->getPiecesNumber()));
    piece_height->setText("Altezza pezzo: " + QString::number(cv->getPieceHeight()));
    piece_lenght->setText("Larghezza pezzo: " + QString::number(cv->getPieceLenght()));

    collar_radius->setText(QString::number(cv->getCollarRadius()));
    collar_width->setText(QString::number(cv->getCollarWidth()));
    collar_waste->setText(QString::number(cv->getWaste()));

    calcolate->setText("Modifica");

    index = list_index;

}

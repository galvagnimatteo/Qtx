#include "rectangleview.h"

#include <QIntValidator>

RectangleView::RectangleView(QWidget *parent) : View(parent){

    mainlayout = new QVBoxLayout();

    calcolate = new QPushButton("Calcola");

    fabric_height = new QLineEdit();
    n_pieces = new QLineEdit();
    piece_height = new QLineEdit();
    piece_lenght = new QLineEdit();

    fabric_height->setPlaceholderText("Altezza tessuto");
    n_pieces->setPlaceholderText("Numero pezzi");
    piece_height->setPlaceholderText("Altezza pezzo");
    piece_lenght->setPlaceholderText("Larghezza pezzo");

    calcolate->setFixedWidth(200);
    fabric_height->setFixedWidth(200);
    n_pieces->setFixedWidth(200);
    piece_height->setFixedWidth(200);
    piece_lenght->setFixedWidth(200);

    fabric_height->setValidator(new QIntValidator(RawCut::MIN_FABRIC_HEIGHT, RawCut::MAX_FABRIC_HEIGHT, mainlayout));
    n_pieces->setValidator(new QIntValidator(RawCut::MIN_PIECES, RawCut::MAX_PIECES, mainlayout));
    piece_lenght->setValidator(new QIntValidator(0, 99, mainlayout));
    piece_height->setValidator(new QIntValidator(0, 99, mainlayout));

    mainlayout->addWidget(fabric_height);
    mainlayout->addWidget(n_pieces);
    mainlayout->addWidget(piece_height);
    mainlayout->addWidget(piece_lenght);
    mainlayout->addWidget(calcolate);

    connect(calcolate, SIGNAL(clicked(bool)), this, SLOT(addOrModifyRectangleCut()));

    index = -1; //l'indice rappresenta la posizione nella lista, ha significato solo se la view è aperta in "modalità" di modifica.

    this->setContentsMargins(20, 20, 0, 0);
    this->setLayout(mainlayout);

}

RectangleController* RectangleView::getController() const{

    return dynamic_cast<RectangleController*> (View::getController()); //uso il getcontroller di view

}

RectangleController* RectangleView::createController(MainModel* m){

    return new RectangleController(this, m);

}

void RectangleView::addOrModifyRectangleCut(){

    if(calcolate->text() == QString::fromStdString("Modifica")){

        emit modifyRectangleCutSignal(index, fabric_height->text(), n_pieces->text(), piece_height->text(), piece_lenght->text());

    }else{

        emit addRectangleCutSignal(fabric_height->text(), n_pieces->text(), piece_height->text(), piece_lenght->text()); //emette il segnale per il controller, utile per passare parametri al controller

    }

}

void RectangleView::updateFields(int list_index){

    const DeepPtr<RectangleCut> rc = getController()->getCutByIndex(list_index);

    fabric_height->setText(QString::number(rc->getFabricHeight()));
    n_pieces->setText(QString::number(rc->getPiecesNumber()));
    piece_height->setText(QString::number(rc->getPieceHeight()));
    piece_lenght->setText(QString::number(rc->getPieceLenght()));

    calcolate->setText("Modifica");

    index = list_index; //view aperta in "modalità" modifica, viene assegnato l'indice.

}

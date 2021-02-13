#include "rectanglecontroller.h"
#include "View/rectangleview.h"

#include <QMessageBox>

RectangleController::RectangleController(View* v, MainModel* m) : Controller(v, m){

    connect(this, SIGNAL(updateFieldsSignal(int)), getView(), SLOT(updateFields(int)));

}

void RectangleController::addRectangleCut(QString fabric_height, QString n_pieces, QString piece_height, QString piece_width){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check); //toInt e toint (in generale i convertitori di tipo) di QString restituiscono per riferimento un valore bool true se andato tutto bene, false viceversa.

    bool n_pieces_check;
    unsigned int casted_n_pieces = n_pieces.toInt(&n_pieces_check);

    bool piece_height_check;
    unsigned int casted_piece_height = piece_height.toInt(&piece_height_check);

    bool piece_width_check;
    unsigned int casted_piece_width = piece_width.toInt(&piece_width_check);

    if(fabric_height_check && n_pieces_check && piece_height_check && piece_width_check  && casted_piece_height > 0 && casted_piece_width > 0){

        if(casted_fabric_height > RawCut::MAX_FABRIC_HEIGHT || casted_fabric_height < RawCut::MIN_FABRIC_HEIGHT){

            QMessageBox::critical(getView(), "Errore!", "Misure del tessuto non standard.");

        }else if(casted_n_pieces > RawCut::MAX_PIECES || casted_n_pieces < RawCut::MIN_PIECES){

            QMessageBox::critical(getView(), "Errore!", "Numero pezzi non accettabile.");

        }else if(casted_fabric_height < casted_piece_height){

            QMessageBox::critical(getView(), "Errore!", "Il pezzo non può essere più alto del tessuto.");

        }else{

            RectangleCut* rc = new RectangleCut(casted_fabric_height, casted_n_pieces, casted_piece_height, casted_piece_width);

            getModel()->insert(rc);

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void RectangleController::modifyRectangleCut(int index, QString fabric_height, QString n_pieces, QString piece_height, QString piece_width){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check);

    bool n_pieces_check;
    unsigned int casted_n_pieces = n_pieces.toInt(&n_pieces_check);

    bool piece_height_check;
    unsigned int casted_piece_height = piece_height.toInt(&piece_height_check);

    bool piece_width_check;
    unsigned int casted_piece_width = piece_width.toInt(&piece_width_check);

    if(fabric_height_check && n_pieces_check && piece_height_check && piece_width_check && casted_piece_height > 0 && casted_piece_width > 0){

        if(casted_fabric_height > RawCut::MAX_FABRIC_HEIGHT || casted_fabric_height < RawCut::MIN_FABRIC_HEIGHT){

            QMessageBox::critical(getView(), "Errore!", "Misure del tessuto non standard.");

        }else if(casted_n_pieces > RawCut::MAX_PIECES || casted_n_pieces < RawCut::MIN_PIECES){

            QMessageBox::critical(getView(), "Errore!", "Numero pezzi non accettabile.");

        }else if(casted_fabric_height < casted_piece_height){

            QMessageBox::critical(getView(), "Errore!", "Il pezzo non può essere più alto del tessuto.");

        }else{

            getModel()->modifyRectangleCut(index, casted_fabric_height, casted_n_pieces, casted_piece_height, casted_piece_width);

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void RectangleController::updateFields(int index){

    emit updateFieldsSignal(index);

}

const DeepPtr<RectangleCut> RectangleController::getCutByIndex(int index){

    const DeepPtr<RawCut> dptr = getModel()->getCutByIndex(index);
    return dynamic_cast<const RectangleCut*>(&*dptr);

}

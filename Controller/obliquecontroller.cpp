#include "obliquecontroller.h"
#include "View/obliqueview.h"

#include <QMessageBox>

ObliqueController::ObliqueController(View* v, MainModel* m) : Controller(v, m){

    connect(this, SIGNAL(updateFieldsSignal(int)), getView(), SLOT(updateFields(int)));

}

void ObliqueController::addObliqueCut(QString fabric_height, QString n_pieces, QString piece_height, QString piece_width, unsigned int angle){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check);

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

        }else if(ObliqueCut::getPiecesPerDiagonal(casted_fabric_height, casted_piece_height, casted_piece_width, angle) == 0){

            QMessageBox::critical(getView(), "Errore!", "Misure pezzo non corrette.\nIl pezzo è troppo grande per il tessuto.");

        }else{

            ObliqueCut *oc = new ObliqueCut(casted_fabric_height, casted_n_pieces, casted_piece_height, casted_piece_width, angle);

            getModel()->insert(oc);

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void ObliqueController::modifyObliqueCut(int index, QString fabric_height, QString n_pieces, QString piece_height, QString piece_width, unsigned int angle){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check);

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

        }else if(ObliqueCut::getPiecesPerDiagonal(casted_fabric_height, casted_piece_height, casted_piece_width, angle) < 1){

            QMessageBox::critical(getView(), "Errore!", "Misure pezzo non corrette.\nIl pezzo è troppo grande per il tessuto.");

        }else{

            getModel()->modifyObliqueCut(index, casted_fabric_height, casted_n_pieces, casted_piece_height, casted_piece_width, angle);

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void ObliqueController::updateFields(int index){

    emit updateFieldsSignal(index);

}

const DeepPtr<ObliqueCut> ObliqueController::getCutByIndex(int index){

    const DeepPtr<RawCut> dptr = getModel()->getCutByIndex(index);
    return dynamic_cast<const ObliqueCut*>(&*dptr);

}

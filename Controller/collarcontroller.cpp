#include "collarcontroller.h"
#include "View/collarview.h"

#include <QMessageBox>

CollarController::CollarController(View* v, MainModel* m) : Controller(v, m){

    connect(getView(), SIGNAL(addCollarCutSignal(QString, QString, QString, QString, QString)),
            this, SLOT(addCollarCut(QString, QString, QString, QString, QString)));

    connect(this, SIGNAL(updateFieldsSignal(int)), getView(), SLOT(updateFields(int)));
    connect(getView(), SIGNAL(modifyCollarCutSignal(int, QString, QString, QString, QString, QString)), this, SLOT(modifyCollarCut(int, QString, QString, QString, QString, QString)));
    connect(this, SIGNAL(updatePieceMeasuresSignal(unsigned int, unsigned int)), getView(), SLOT(updatePieceMeasures(unsigned int, unsigned int)));

}

void CollarController::addCollarCut(QString fabric_height, QString n_pieces, QString collar_width, QString collar_radius, QString waste){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check);

    bool n_pieces_check;
    unsigned int casted_n_pieces = n_pieces.toInt(&n_pieces_check);

    bool collar_width_check;
    unsigned int casted_collar_width = collar_width.toInt(&collar_width_check);

    bool collar_radius_check;
    unsigned int casted_collar_radius = collar_radius.toInt(&collar_radius_check);

    bool waste_check;
    unsigned int casted_waste = waste.toInt(&waste_check);

    if(fabric_height_check && n_pieces_check && collar_radius_check && collar_width_check && waste_check){

        if(casted_fabric_height > RawCut::MAX_FABRIC_HEIGHT || casted_fabric_height < RawCut::MIN_FABRIC_HEIGHT){

            QMessageBox::critical(getView(), "Errore!", "Misure del tessuto non standard.");

        }else if(casted_n_pieces > RawCut::MAX_PIECES || casted_n_pieces < RawCut::MIN_PIECES){

            QMessageBox::critical(getView(), "Errore!", "Numero pezzi non accettabile.");

        }else if(casted_fabric_height < CollarCut::computePieceHeight(casted_collar_width, casted_collar_radius)){

            QMessageBox::critical(getView(), "Errore!", "Il pezzo generato è più alto del tessuto.");

        }else if(casted_collar_radius > CollarCut::MAX_COLLAR_RADIUS || casted_collar_radius < CollarCut::MIN_COLLAR_RADIUS || casted_collar_width < CollarCut::MIN_COLLAR_WIDTH || casted_collar_width > CollarCut::MAX_COLLAR_WIDTH || casted_waste < CollarCut::MIN_COLLAR_WASTE){

            QMessageBox::critical(getView(), "Errore!", "Misure del colletto non standard.");

        }else{

            CollarCut* cc = new CollarCut(casted_fabric_height, casted_n_pieces, casted_collar_width, casted_collar_radius, casted_waste);

            getModel()->insert(cc);

            emit updatePieceMeasuresSignal(cc->getPieceHeight(), cc->getPieceLenght());

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void CollarController::modifyCollarCut(int index, QString fabric_height, QString n_pieces, QString collar_width, QString collar_radius, QString collar_waste){

    bool fabric_height_check;
    unsigned int casted_fabric_height = fabric_height.toInt(&fabric_height_check);

    bool n_pieces_check;
    unsigned int casted_n_pieces = n_pieces.toInt(&n_pieces_check);

    bool collar_width_check;
    unsigned int casted_collar_width = collar_width.toInt(&collar_width_check);

    bool collar_radius_check;
    unsigned int casted_collar_radius = collar_radius.toInt(&collar_radius_check);

    bool waste_check;
    unsigned int casted_waste = collar_waste.toInt(&waste_check);

    if(fabric_height_check && n_pieces_check && collar_radius_check && collar_width_check && waste_check){

        if(casted_fabric_height > RawCut::MAX_FABRIC_HEIGHT || casted_fabric_height < RawCut::MIN_FABRIC_HEIGHT){

            QMessageBox::critical(getView(), "Errore!", "Misure del tessuto non standard.");

        }else if(casted_n_pieces > RawCut::MAX_PIECES || casted_n_pieces < RawCut::MIN_PIECES){

            QMessageBox::critical(getView(), "Errore!", "Numero pezzi non accettabile.");

        }else if(casted_fabric_height < CollarCut::computePieceHeight(casted_collar_width, casted_collar_radius)){

            QMessageBox::critical(getView(), "Errore!", "Il pezzo generato è più alto del tessuto.");

        }else if(casted_collar_radius > CollarCut::MAX_COLLAR_RADIUS || casted_collar_radius < CollarCut::MIN_COLLAR_RADIUS || casted_collar_width < CollarCut::MIN_COLLAR_WIDTH || casted_collar_width > CollarCut::MAX_COLLAR_WIDTH){

            QMessageBox::critical(getView(), "Errore!", "Misure del colletto non standard.");

        }else{

            getModel()->modifyCollarCut(index, casted_fabric_height, casted_n_pieces, casted_collar_width, casted_collar_radius, casted_waste);

            emit updateFieldsSignal(index); //necessario per aggiornare le due caselle di testo disabilitate

        }

    }else{

        QMessageBox::critical(getView(), "Errore!", "Dati mancanti o non corretti.");

    }

}

void CollarController::updateFields(int index){

    emit updateFieldsSignal(index);

}

const DeepPtr<CollarCut> CollarController::getCutByIndex(int index){

    const DeepPtr<RawCut> dptr = getModel()->getCutByIndex(index);
    return dynamic_cast<const CollarCut*>(&*dptr);

}

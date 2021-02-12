#ifndef COLLARCONTROLLER_H
#define COLLARCONTROLLER_H

#include <QObject>

#include "Model/collarcut.h"
#include "controller.h"

class CollarView;

class CollarController: public Controller {

    Q_OBJECT

public:

    CollarController(View* v, MainModel* m);

    void updateFields(int);

    const DeepPtr<CollarCut> getCutByIndex(int);

public slots:

    void addCollarCut(QString, QString, QString, QString, QString);
    void modifyCollarCut(int, QString, QString, QString, QString, QString);

signals:

    void updateFieldsSignal(int);
    void updatePieceMeasuresSignal(unsigned int, unsigned int);

};

#endif

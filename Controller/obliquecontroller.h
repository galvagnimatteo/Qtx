#ifndef OBLIQUECONTROLLER_H
#define OBLIQUECONTROLLER_H

#include <QObject>

#include "Model/obliquecut.h"
#include "controller.h"

class ObliqueView;

class ObliqueController: public Controller {

    Q_OBJECT

public:

    ObliqueController(View* v, MainModel* m);

    void updateFields(int);

    const DeepPtr<ObliqueCut> getCutByIndex(int);

public slots:

    void addObliqueCut(QString, QString, QString, QString, unsigned int);
    void modifyObliqueCut(int, QString, QString, QString, QString, unsigned int);

signals:

    void updateFieldsSignal(int);

};

#endif

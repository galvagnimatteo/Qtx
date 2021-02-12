#ifndef RECTANGLECONTROLLER_H
#define RECTANGLECONTROLLER_H

#include <QObject>

#include "Model/rectanglecut.h"
#include "controller.h"

class RectangleView;

class RectangleController: public Controller {

    Q_OBJECT

public:

    RectangleController(View* v, MainModel* m);

    void updateFields(int);

    const DeepPtr<RectangleCut> getCutByIndex(int);

public slots:

    void addRectangleCut(QString, QString, QString, QString);
    void modifyRectangleCut(int, QString, QString, QString, QString);

signals:

    void updateFieldsSignal(int);

};

#endif

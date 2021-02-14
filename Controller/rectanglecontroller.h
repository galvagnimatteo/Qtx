#ifndef RECTANGLECONTROLLER_H
#define RECTANGLECONTROLLER_H

#include <QObject>
#include <QMessageBox>

#include "Model/rectanglecut.h"
#include "controller.h"

class RectangleController: public Controller {

    Q_OBJECT

public:

    RectangleController(View* v, MainModel* m); //non posso passare una rectangleview dichiarata in modo incompleto perchè non include l'informazione che deriva da View

    void updateFields(int);

    const DeepPtr<RectangleCut> getCutByIndex(int);
    void addRectangleCut(QString, QString, QString, QString);
    void modifyRectangleCut(int, QString, QString, QString, QString);

signals:

    void updateFieldsSignal(int);

};

#endif

#ifndef RECTANGLEWINDOWCONTROLLER_H
#define RECTANGLEWINDOWCONTROLLER_H

#include <QObject>
#include "Model/obliquecut.h"
#include "Model/collarcut.h"
#include "Model/rectanglecut.h"
#include "controller.h"
#include "View/collarview.h"
#include "View/obliqueview.h"
#include "View/rectangleview.h"
#include "View/view.h"

class RectangleWindowController : public Controller {

    Q_OBJECT

public:

    RectangleWindowController(View* v, MainModel* m);

public slots:

    void openObliqueLayout(int index = -1);
    void openRectangleLayout(int index = -1);
    void openCollarLayout(int index = -1);

    void emitLockViewSignal();
    void emitUnlockViewSignal();

signals:

    void lockViewSignal();
    void unlockViewSignal();
    void changeLayoutSignal(View*);

};

#endif

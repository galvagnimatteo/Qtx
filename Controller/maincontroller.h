#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "Model/mainmodel.h"
#include "Model/rectanglecut.h"
#include "controller.h"

class MainWindow;

class MainController : public Controller {

    Q_OBJECT

public:

    MainController(View*, MainModel* m);

    C<DeepPtr<RawCut>> getAllCuts() const;
    void openModifyView(int);
    void deleteSelectedCut(int);

public slots:

    void openRectangleWindow();

};

#endif

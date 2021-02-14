#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "Model/mainmodel.h"
#include "controller.h"
#include "View/view.h"

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

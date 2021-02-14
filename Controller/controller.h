#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "View/view.h"

class Controller: public QObject{

    Q_OBJECT

private:

    MainModel* m;
    View* v;

public:

    Controller(View* v, MainModel* m);
    virtual ~Controller() = default;

    MainModel* getModel() const;
    View* getView() const;

};

#endif

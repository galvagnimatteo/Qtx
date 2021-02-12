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
    //Nelle classi che ereditano da Controller non sarà possibile fare la forward declaration della propria relativa View
    //includendo l'informazione che tale view eredita da View, dunque non sarà possibile ritornare un tipo (esempio)
    //ObliqueView* con getView() perchè ObliqueView sarà definita in modo non completo senza poter includere che deriva da View, quindi non
    //risulterà figlia di View e l'override non funzionerà.
    //Per questo, ogni "figlio" di controller userà la getView di View ed eventualmente farà il dynamic_cast al momento.

};

#endif

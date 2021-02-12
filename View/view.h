#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLayout>

#include "Model/mainmodel.h"

class Controller;

class View: public QWidget{

    Q_OBJECT

private:

    Controller* c;

    virtual Controller* createController(MainModel* m) = 0; //ogni view ridefinirà questo metodo per creare il controller corretto

public:

    View(QWidget* parent = nullptr);

    static void connectViewController(View* v, MainModel* m); //statica perchè non fa riferimento a nessun oggetto di invocazione ma solo all'oggetto passato
    virtual Controller* getController() const;

};

#endif

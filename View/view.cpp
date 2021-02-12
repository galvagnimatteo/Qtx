#include "view.h"
#include "Controller/controller.h"

View::View(QWidget *parent) : QWidget(parent), c(nullptr){ }

Controller* View::getController() const{

    return this->c;

}

void View::connectViewController(View *v, MainModel* m){

    v->c = v->createController(m);

}

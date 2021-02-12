#include "controller.h"

Controller::Controller(View *v, MainModel *m): QObject(v), m(m), v(v){ }

View* Controller::getView() const{

    return this->v;

}

MainModel* Controller::getModel() const{

    return this->m;

}

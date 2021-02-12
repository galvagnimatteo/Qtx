#include "View/mainwindow.h"
#include "Controller/maincontroller.h"
#include "Model/mainmodel.h"

#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow w;
    MainModel m;

    View::connectViewController(&w, &m);

    w.show();

    //a.setWindowIcon(QIcon(":resources/resources/.png"));

    return a.exec();

}

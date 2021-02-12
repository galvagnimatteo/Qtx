#include "View/mainwindow.h"
#include "Controller/maincontroller.h"

MainWindow::MainWindow(QWidget *parent): View(parent) {

    isLocked = false;

    QHBoxLayout* mainLayout = new QHBoxLayout;

    addList(mainLayout);
    addButtons(mainLayout);

    connect(modifyCut, SIGNAL(clicked(bool)), this, SLOT(modifySelectedCut()));
    connect(deleteCut, SIGNAL(clicked(bool)), this, SLOT(deleteSelectedCut()));

    setLayout(mainLayout);
    resize(QSize(1024, 720));

}

void MainWindow::closeEvent(QCloseEvent *event){

    if(isLocked){

        event->ignore(); //ignora la chiusura della mainwindow se è bloccata (non interagibile)

    }else{

        event->accept();

    }

}


void MainWindow::addList(QHBoxLayout* mainLayout) {

     listwidget = new QListWidget();

     listwidget->setStyleSheet("QListWidget::item { border: 1.5px solid grey; background-color: #EEEEEE} QListWidget::item::selected { border: 1.5px solid #333333; background-color: #CCCCCC };");

     listwidget->setSpacing(3);

     mainLayout->addWidget(listwidget);

}

void MainWindow::addButtons(QHBoxLayout* mainLayout) {

    QVBoxLayout* buttonsLayout = new QVBoxLayout;

    addRectangleCut = new QPushButton("Taglio grezzo rettangolare");
    modifyCut = new QPushButton("Modifica selezionato");
    deleteCut = new QPushButton("Elimina selezionato");

    buttonsLayout->addWidget(addRectangleCut);
    buttonsLayout->addWidget(modifyCut);
    buttonsLayout->addWidget(deleteCut);
    buttonsLayout->setSpacing(5);

    buttonsLayout->setContentsMargins(20, 0, 0, 0);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addLayout(buttonsLayout);

}

MainController* MainWindow::createController(MainModel* m){

    MainController* mc = new MainController(this, m);

    connect(addRectangleCut, SIGNAL(clicked(bool)), mc, SLOT(openRectangleWindow()));

    return mc;
}

MainController* MainWindow::getController() const{

    return dynamic_cast<MainController*> (View::getController());

}

void MainWindow::updateView(){

    listwidget->clear();

    C<DeepPtr<RawCut>> list = getController()->getAllCuts();

    for(auto it = list.begin(); it!=list.end(); ++it){

        DeepPtr<RawCut> a = *it;

        //tostring dei tagli
        listwidget->addItem(QString::fromStdString(a->toString()) + "CONSUMO CALCOLATO: " + QString::number(a->getConsumption()) + "cm");

    }


}

void MainWindow::modifySelectedCut(){

    if(listwidget->selectionModel()->selectedIndexes().size() == 1){

        emit modifySelectedCutSignal(listwidget->selectionModel()->selectedIndexes()[0].row()); //appurato che sia selezionato un solo item nella listwidget, viene emesso il segnale con l'indice intero
                                                                                                //che sarà in posizione 0 della lista degli indici fornita da selectedindexes().

    }else{

        emit modifySelectedCutSignal(-1);

    }

}

void MainWindow::deleteSelectedCut(){

    if(listwidget->selectionModel()->selectedIndexes().size() == 1){

        emit deleteSelectedCutSignal(listwidget->selectionModel()->selectedIndexes()[0].row());

    }else{

        emit deleteSelectedCutSignal(-1);

    }

}

void MainWindow::lockView(){

    this->setWindowFlag(Qt::WindowTransparentForInput);
    this->setWindowFlag(Qt::WindowDoesNotAcceptFocus);
    isLocked = true;
    this->show();

}

void MainWindow::unlockView(){

    this->setWindowFlag(Qt::WindowTransparentForInput, false);
    this->setWindowFlag(Qt::WindowDoesNotAcceptFocus, false);
    isLocked = false;
    this->show();

}


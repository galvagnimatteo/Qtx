#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QCloseEvent>

#include "Controller/maincontroller.h"
#include "view.h"

class MainWindow: public View{

    Q_OBJECT

private:

    bool isLocked;

    QPushButton* addRectangleCut;
    QPushButton* modifyCut;
    QPushButton* deleteCut;

    QListWidget* listwidget;

    void addList(QHBoxLayout* mainLayout);
    void addButtons(QHBoxLayout* mainLayout);

    MainController* createController(MainModel* m) override;

    void closeEvent(QCloseEvent *event) override;

public:

    MainWindow(QWidget *parent = nullptr);

    MainController* getController() const override;

public slots:

    void updateView();
    void modifySelectedCut();
    void deleteSelectedCut();
    void lockView();
    void unlockView();

signals:

    void modifySelectedCutSignal(int);
    void deleteSelectedCutSignal(int);

};

#endif

#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>

#include "View/obliqueview.h"
#include "View/collarview.h"
#include "View/rectangleview.h"
#include <QCloseEvent>

#include "Controller/rectanglewindowcontroller.h"

class RectangleWindow : public View{

    Q_OBJECT

private:

    QHBoxLayout* mainLayout;
    QVBoxLayout* buttonsLayout;

    QGroupBox* groupBox;
    QRadioButton* rectangle;
    QRadioButton* oblique;
    QRadioButton* collar;

    void addButtons(QHBoxLayout* mainLayout);
    RectangleWindowController* createController(MainModel* m) override;

    //override di showEvent e closeEvent per abilitare e disabilitare la mainview rispettivamente quando rectanglewindow viene mostrata (quindi con controller già assegnato) e quando viene chiusa.
    void closeEvent (QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

public:

    RectangleWindow(QWidget *parent = nullptr);

    RectangleWindowController* getController() const override;

    void changeLayout(View*);

    void setRectangleButtonSelected();
    void setObliqueButtonSelected();
    void setCollarButtonSelected();
    void disableRadioGroup();

signals:

    void lockViewSignal();
    void unlockViewSignal();

};

#endif

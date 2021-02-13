#ifndef OBLIQUELAYOUT_H
#define OBLIQUELAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>

#include "rectanglewindow.h"
#include "Controller/obliquecontroller.h"
#include "view.h"

class ObliqueView: public View{

    Q_OBJECT

private:

    QHBoxLayout* mainlayout;

    QVBoxLayout* rectanglecutlayout;
    QVBoxLayout* obliquecutlayout;
    QVBoxLayout* groupboxlayout;

    QLineEdit* fabric_height;
    QLineEdit* n_pieces;
    QLineEdit* piece_lenght;
    QLineEdit* piece_height;

    //checkbox con i gradi di inclinazione

    QGroupBox* groupBox;
    QRadioButton* degrees30;
    QRadioButton* degrees45;
    QRadioButton* degrees60;

    QPushButton* calcolate;

    int index;

    ObliqueController* createController(MainModel* m) override;

public:

    ObliqueView(QWidget* parent = nullptr);

    ObliqueController* getController() const override;

public slots:

    void addOrModifyObliqueCut();
    void updateFields(int);

};

#endif

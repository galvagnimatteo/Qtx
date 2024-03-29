#ifndef RECTANGLELAYOUT_H
#define RECTANGLELAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include "Controller/rectanglecontroller.h"

class RectangleView: public View{

    Q_OBJECT

private:

    QVBoxLayout* mainlayout;
    QLineEdit* fabric_height;
    QLineEdit* n_pieces;
    QLineEdit* piece_lenght;
    QLineEdit* piece_height;
    QPushButton* calcolate;

    int index;

    RectangleController* createController(MainModel* m) override;

public:

    RectangleView(QWidget* parent = nullptr);

    RectangleController* getController() const override;

public slots:

    void addOrModifyRectangleCut();
    void updateFields(int);

};

#endif

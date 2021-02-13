#ifndef COLLARLAYOUT_H
#define COLLARLAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include "Controller/collarcontroller.h"
#include "view.h"

class CollarView: public View{

    Q_OBJECT

private:

    QHBoxLayout* mainlayout;

    QVBoxLayout* rectanglecutlayout;
    QVBoxLayout* collarcutlayout;

    QLineEdit* fabric_height;
    QLineEdit* n_pieces;
    QLineEdit* piece_lenght;
    QLineEdit* piece_height;

    QLineEdit* collar_radius;
    QLineEdit* collar_width;
    QLineEdit* collar_waste;

    QPushButton* calcolate;

    int index;

    CollarController* createController(MainModel* m) override;

public:

    CollarView(QWidget* parent = nullptr);

    CollarController* getController() const override;

public slots:

    void addOrModifyCollarCut();
    void updateFields(int);
    void updatePieceMeasures(unsigned int, unsigned int);

};

#endif

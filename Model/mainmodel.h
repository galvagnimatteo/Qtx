#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "Model/c.h"
#include "Model/rawcut.h"
#include "Model/deepptr.h"
#include "obliquecut.h"
#include "collarcut.h"

#include <QString>
#include <QObject>

class MainModel: public QObject{

    Q_OBJECT

private:

    C<DeepPtr<RawCut>>* cuts_list;

public:

    MainModel(QObject *parent = nullptr);

    void insert(const DeepPtr<RawCut>&);
    void removeByIndex(int);
    const DeepPtr<RawCut> getCutByIndex(int) const;
    C<DeepPtr<RawCut>> getAllCuts() const;

    void modifyRectangleCut(int, unsigned int, unsigned int, unsigned int, unsigned int);
    void modifyObliqueCut(int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    void modifyCollarCut(int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

signals:

    void modelUpdated();

};

#endif

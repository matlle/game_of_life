/*
* Created by Koukougnon Martial Babo on 10/15/19.
*/
#ifndef GOL_CELLITEM_H
#define GOL_CELLITEM_H

#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QBrush>
#include <QtWidgets/QMessageBox>

#include "headers/MainWindow.h"
#include "headers/GridView.h"


class CellItem : public QGraphicsRectItem {
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    MainWindow *mainWindow = nullptr;

public:
    ~CellItem() override;
    void setMainWindow(MainWindow *);
};

#endif //GOL_CELLITEM_H

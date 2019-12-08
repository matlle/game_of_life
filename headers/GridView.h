/*
* Created by Koukougnon Martial Babo on 10/15/19.
*/
#ifndef GOL_GRIDVIEW_H
#define GOL_GRIDVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include <QDebug>

class GridView : public QGraphicsView {
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *) override;
};

#endif //GOL_GRIDVIEW_H

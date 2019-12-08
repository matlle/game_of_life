/*
* Created by Koukougnon Martial Babo on 10/15/19.
*/
#include "headers/CellItem.h"

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mousePressEvent(event);
    if(!event->isAccepted()) {
        if(event->button() == Qt::LeftButton) {
            if(this->mainWindow != nullptr) {
                if(this->mainWindow->currentGeneration > 0) {
                    QMessageBox::StandardButton btnClicked = QMessageBox::question(this->mainWindow->centralWidget(), QString("Reset grid"),QString("Do you want reset the grid?"));
                    if (btnClicked == QMessageBox::Yes) {
                        this->mainWindow->cleanMainGrid();
                        this->mainWindow->currentGeneration = 0;
                    }
                }
            }
            this->brush() != QBrush() ? this->setBrush(QBrush()) : this->setBrush(QBrush(0x423e3f, Qt::SolidPattern));
            int x = (int)this->rect().x() / this->mainWindow->cellWidth;
            int y = (int)this->rect().y() / this->mainWindow->cellWidth;
            this->brush() != QBrush() ? this->mainWindow->grid[x][y] = 1 : this->mainWindow->grid[x][y] = 0;
        }
    }
}

void CellItem::setMainWindow(MainWindow *window) {
    this->mainWindow = window;
}

CellItem::~CellItem() {
    delete mainWindow;
}
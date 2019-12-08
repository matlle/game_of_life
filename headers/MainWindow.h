/*
* Created by Koukougnon Martial Babo on 10/15/19.
*/
#ifndef GOL_MAINWINDOW_H
#define GOL_MAINWINDOW_H

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include "GridView.h"

#define GRID_ROWS 20;
#define GRID_COLS 20;

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    int countAliveNeighbors(int, int);

    QMenuBar *menuBar = nullptr;
    QMenu *settingsMenu = nullptr;
    QAction *nextGenerationAction = nullptr;
    QAction *cleanGridAction = nullptr;
    QAction *exitAction = nullptr;
    QWidget *widget = nullptr;
    QGridLayout *mainLayout = nullptr;
    QGraphicsSimpleTextItem *currentGenerationText = nullptr;
    GridView *gridView = nullptr;
    QGraphicsScene *scene = nullptr;
    std::vector<QGraphicsRectItem*> cells;
    int numberOfCellsOnX = GRID_ROWS;
    int numberOfCellsOnY = GRID_COLS;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override ;
    void createMenuBar();
    void setupMainGrid();
    bool isMainGridInitialized();

    int currentGeneration = 0;
    int cellWidth = 25;
    int cellHeight = 25;
    int grid[20][20];
    int nextGrid[20][20];

public slots:
    void nextGeneration();
    void cleanMainGrid();
    void exit();
};


#endif //GOL_MAINWINDOW_H

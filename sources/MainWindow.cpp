/*
* Created by Koukougnon Martial Babo on 10/15/19.
*/
#include "headers/MainWindow.h"
#include "headers/GridView.h"
#include "headers/CellItem.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->createMenuBar();
    widget = new QWidget(this);
    mainLayout = new QGridLayout(widget);
    mainLayout->setMenuBar(menuBar);
    widget->setLayout(mainLayout);
    this->setCentralWidget(widget);
    setupMainGrid();
    this->setWindowTitle("Game Of Life v.0.0.1 -- by Koukougnon Martial Babo");
    this->showMaximized();
}

void MainWindow::createMenuBar() {
    this->menuBar = new QMenuBar();
    this->settingsMenu = new QMenu("&Settings", this);
    this->cleanGridAction = settingsMenu->addAction("&Reset grid");
    this->exitAction = this->settingsMenu->addAction("&Exit");
    this->menuBar->addMenu(this->settingsMenu);
    this->nextGenerationAction = this->menuBar->addAction("Next generation >>");

    QObject::connect(this->nextGenerationAction, SIGNAL(triggered()), this, SLOT(nextGeneration()));
    QObject::connect(this->cleanGridAction, SIGNAL(triggered()), this, SLOT(cleanMainGrid()));
    QObject::connect(this->exitAction, SIGNAL(triggered()), this, SLOT(exit()));
}

void MainWindow::setupMainGrid() {
    this->scene = new QGraphicsScene();
    this->cells = {};
    int resolution = this->cellWidth;
    int firstDrawingX = true;

    this->currentGenerationText = new QGraphicsSimpleTextItem();
    this->currentGenerationText->setText("Generation: " + QString::number(this->currentGeneration));
    QFont font("Times", 18, QFont::Bold);
    this->currentGenerationText->setFont(font);
    this->currentGenerationText->setX(0);
    this->currentGenerationText->setY(-40);
    scene->addItem(this->currentGenerationText);

    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            this->grid[x][y] = 0;
        }
    }

    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            int posX = x * resolution;
            int posY = y * resolution;
            auto *rect = new CellItem();
            rect->setRect(posX, posY, resolution, resolution);
            rect->setMainWindow(this);
            scene->addItem(rect);
            this->cells.push_back(rect);
        }
    }
    this->gridView = new GridView();
    gridView->setScene(scene);
    gridView->setParent(this->widget);
    this->mainLayout->addWidget(gridView, 0, 0);
}

int MainWindow::countAliveNeighbors(int y, int x) {
    int alives = 0;
    for(int y1 = -1; y1 < 2; y1++) {
        for(int x1 = -1; x1 < 2; x1++) {
            int col = (x + y1 + this->numberOfCellsOnY) % this->numberOfCellsOnY;
            int row = (y + x1 + this->numberOfCellsOnX) % this->numberOfCellsOnX;
            alives += this->grid[col][row];
        }
    }
    alives -= this->grid[x][y];
    return alives;
}
void MainWindow::nextGeneration() {
    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            this->nextGrid[x][y] = this->grid[x][y];
        }
    }

    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            int state = this->grid[x][y];
            int aliveNeighbors = this->countAliveNeighbors(y, x);
            if(state == 0 && aliveNeighbors == 3) {
                this->nextGrid[x][y] = 1;
            } else if(state == 1 && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
                this->nextGrid[x][y] = 0;
            } else {
                this->nextGrid[x][y] = state;
            }
        }
    }

    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            this->grid[x][y] = this->nextGrid[x][y];
        }
    }

    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            auto *item = qgraphicsitem_cast<QGraphicsRectItem*>(this->scene->itemAt((double)x * this->cellWidth, (double)y * this->cellHeight, QTransform()));
            if(item != nullptr) {
                this->grid[x][y] == 1 ? item->setBrush(QBrush(0x423e3f, Qt::SolidPattern)) : item->setBrush(QBrush());
            }
        }
    }
    this->currentGenerationText->setText("Generation: " + QString::number(++this->currentGeneration));
}

void MainWindow::cleanMainGrid() {
    this->currentGeneration = 0;
    this->currentGenerationText->setText("Generation: " + QString::number(0));
    for(int y = 0; y < this->numberOfCellsOnY; y++) {
        for(int x = 0; x < this->numberOfCellsOnX; x++) {
            this->grid[x][y] = 0;
        }
    }
    for(auto i: this->cells) {
        if(i != nullptr) {
            i->setBrush(QBrush());
        }
    }
}

bool MainWindow::isMainGridInitialized() {
    bool b = false;
    for(auto i: this->cells) {
        if(i != nullptr) {
            b = i->brush() != QBrush();
            if(b) break;
        }
    }
    return b;
}

void MainWindow::exit() {
    QApplication::quit();
}

MainWindow::~MainWindow() {
    delete menuBar;
    delete settingsMenu;
    delete nextGenerationAction;
    delete cleanGridAction;
    delete exitAction;
    delete widget;
    delete mainLayout;
    delete currentGenerationText;
    delete gridView;
    delete scene;
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"
#include "coordinates.h"
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <random>
#include <unordered_set>
#include <vector>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QTimer*                         timer;
        std::vector<Ball>               particles;
        std::unordered_set<coordinates> occupied;
        std::mt19937                    rng{std::random_device{}()};

        int windowHeight  = 600;
        int windowWidth   = 800;
        int gridWidth     = windowWidth / cellSize;
        int gridHeight    = windowHeight / cellSize;
        int spawnInterval = 6;
        int tickCount     = 0;

    private slots:
        void updateGame();
};
#endif // MAINWINDOW_H

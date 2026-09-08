#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "coordinates.h"
#include "grid.h"
#include "particle.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <random>
#include <vector>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    protected:
        void paintEvent(QPaintEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    private:
        QTimer*               timer;
        std::vector<Particle> particles;
        std::mt19937          rng{std::random_device{}()};
        QPixmap               settledLayer;
        void                  moveCursor();
        void                  step();

        int         windowHeight  = 600;
        int         windowWidth   = 800;
        int         gridWidth     = windowWidth / cellSize;
        int         gridHeight    = windowHeight / cellSize;
        int         spawnInterval = 1;
        int         stepsPerFrame = 4;
        int         tickCount     = 0;
        int         settledCount  = 0;
        coordinates cursorPos     = {gridWidth / 2, 0};
        bool        leftPressed   = false;
        bool        rightPressed  = false;
        bool        downPressed   = false;
        bool        upPressed     = false;
        Grid        grid{gridWidth, gridHeight};

    private slots:
        void updateGame();
};
#endif // MAINWINDOW_H

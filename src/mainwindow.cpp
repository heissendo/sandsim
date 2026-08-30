
#include "mainwindow.h"
#include <QKeyEvent>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(windowWidth, windowHeight);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);
}

MainWindow::~MainWindow() = default;

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    for (const Ball& particle : particles)
    {
        particle.draw(painter);
    }
}

void MainWindow::updateGame()
{
    moveCursor();

    if (tickCount++ % spawnInterval == 0)
    {
        const coordinates spawn{cursorPos.x, 0};
        std::cout << "Spawn: (" << spawn.x << ", " << spawn.y << ")"
                  << std::endl;

        if (!occupied.contains(spawn))
        {
            particles.emplace_back(spawn);
            occupied.insert(spawn);
        }
    }

    for (Ball& particle : particles)
    {
        if (particle.isSettled())
        {
            continue;
        }
        const coordinates from = particle.getCell();
        particle.move(occupied, gridWidth, gridHeight, rng);
        const coordinates to = particle.getCell();

        if (!(from == to))
        {
            occupied.erase(from);
            occupied.insert(to);
        }
    }

    update();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
        leftPressed = true;
    if (event->key() == Qt::Key_Right)
        rightPressed = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
        leftPressed = false;
    if (event->key() == Qt::Key_Right)
        rightPressed = false;
}

void ::MainWindow::moveCursor()
{
    if (leftPressed && cursorPos.x > 0)
    {
        cursorPos.x--;
    }
    if (rightPressed && cursorPos.x < gridWidth - 1)
    {
        cursorPos.x++;
    }
}

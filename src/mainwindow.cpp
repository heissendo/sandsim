
#include "mainwindow.h"
#include <QKeyEvent>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(windowWidth, windowHeight);

    settledLayer = QPixmap(windowWidth, windowHeight);
    settledLayer.fill(palette().color(QPalette::Window));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);
}

MainWindow::~MainWindow() = default;

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, settledLayer);

    for (const Ball& particle : particles)
    {
        particle.draw(painter);
    }
}

void MainWindow::updateGame()
{
    moveCursor();

    for (int i = 0; i < stepsPerFrame; i++)
    {
        step();
    }

    if (!justSettled.empty())
    {
        QPainter painter(&settledLayer);
        for (const Ball& particle : justSettled)
        {
            particle.draw(painter);
        }
        justSettled.clear();
    }

    update();
}

void MainWindow::step()
{
    if (tickCount++ % spawnInterval == 0)
    {
        const coordinates spawn{cursorPos.x, 0};

        if (grid.getCell(spawn) == Cell::Empty)
        {
            particles.emplace_back(spawn);
            grid.setCell(spawn, Cell::Falling);
        }
    }

    for (Ball& particle : particles)
    {
        const coordinates from = particle.getCell();
        particle.move(grid, rng);
        const coordinates to = particle.getCell();

        if (!(from == to))
        {
            grid.setCell(from, Cell::Empty);
            grid.setCell(to, Cell::Falling);
        }

        if (particle.isSettled())
        {
            grid.setCell(to, Cell::Settled);
            particle.setColor(settledCount++);
            justSettled.push_back(particle);
        }
    }

    std::erase_if(particles, [](const Ball& b) { return b.isSettled(); });
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

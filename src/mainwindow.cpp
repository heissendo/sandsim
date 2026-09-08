
#include "mainwindow.h"
#include <QKeyEvent>
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), grid(gridWidth, gridHeight)
{
    setWindowTitle("sandsim");
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
    // Stamp newly stopped grains into the offscreen image, not the screen.
    {
        QPainter layerPainter(&settledLayer);
        for (const Particle& particle : particles)
        {
            if (particle.isSettled())
            {
                particle.draw(layerPainter);
            }
        }
    }

    // stop simulating them.
    std::erase_if(particles, [](const Particle& p) { return p.isSettled(); });

    // One blit draws the whole pile
    QPainter widgetPainter(this);
    widgetPainter.drawPixmap(0, 0, settledLayer);

    // Falling grains move every frame
    for (const Particle& particle : particles)
    {
        particle.draw(widgetPainter);
    }

    widgetPainter.setBrush((Qt::blue));
    widgetPainter.drawRect(cursorPos.x * cellSize - 3,
                           cursorPos.y * cellSize - 3, cellSize + 6,
                           cellSize + 6);
}

void MainWindow::updateGame()
{
    moveCursor();

    for (int i = 0; i < stepsPerFrame; i++)
    {
        step();
    }

    update();
}

void MainWindow::step()
{
    if (tickCount++ % spawnInterval == 0)
    {
        const coordinates spawn{cursorPos.x, cursorPos.y};

        if (grid.getCell(spawn) == Cell::Empty)
        {
            particles.emplace_back(spawn);
            grid.setCell(spawn, Cell::Falling);
        }
    }

    for (Particle& particle : particles)
    {
        const coordinates from = particle.getCell();
        particle.move(grid, rng);
        const coordinates to = particle.getCell();

        if (!(from == to))
        {
            grid.setCell(from, Cell::Empty);
            grid.setCell(to, Cell::Falling);
        }

        if (particle.isSettled() && !particle.isColorSet())
        {
            grid.setCell(to, Cell::Settled);
            particle.setColor(settledCount++);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
        leftPressed = true;
    if (event->key() == Qt::Key_Right)
        rightPressed = true;
    if (event->key() == Qt::Key_Down)
        downPressed = true;
    if (event->key() == Qt::Key_Up)
        upPressed = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
        leftPressed = false;
    if (event->key() == Qt::Key_Right)
        rightPressed = false;
    if (event->key() == Qt::Key_Down)
        downPressed = false;
    if (event->key() == Qt::Key_Up)
        upPressed = false;
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
    if (downPressed && cursorPos.y < gridHeight - 1)
    {
        cursorPos.y++;
    }
    if (upPressed && cursorPos.y > 0)
    {
        cursorPos.y--;
    }
}

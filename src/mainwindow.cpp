
#include "mainwindow.h"

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
    if (tickCount++ % spawnInterval == 0)
    {
        const coordinates spawn{gridWidth / 2, 0};

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

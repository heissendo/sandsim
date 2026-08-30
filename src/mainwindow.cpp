
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(windowWidth, windowHeight);
    ball = new Ball(windowWidth / 2, 0, 15, 1, 1, windowWidth, windowHeight);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ball;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Create QPainter to draw on the widget
    ball->draw(painter);
}

void MainWindow::updateGame()
{

    ball->move();
    update();
}

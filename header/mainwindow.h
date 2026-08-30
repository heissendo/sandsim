#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <unordered_set>

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

        struct coordinates
        {
                int  x;
                int  y;
                bool operator==(const coordinates& o) const
                {
                    return x == o.x && y == o.y;
                }
        };

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        Ball*   ball;
        QTimer* timer;
        int     windowHeight = 600;
        int     windowWidth  = 800;

    private slots:
        void updateGame();
};
#endif // MAINWINDOW_H

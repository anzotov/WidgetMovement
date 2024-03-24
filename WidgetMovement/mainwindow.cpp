#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    m_timer = new QTimer(this);
    m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, m_timer, [this]()
            {
        constexpr int minTimeMs = 100, maxTimeMs = 1000;
        this->m_timer->setInterval(QRandomGenerator::global()->bounded(minTimeMs, maxTimeMs));
        auto button = new QPushButton(this);
        auto windowSize = this->size();
        auto buttonSize = QSize(10, 10);
        auto position = QPoint(QRandomGenerator::global()->bounded(0, windowSize.width()-buttonSize.width()), 100);
        button->setGeometry(QRect(position, buttonSize));
        button->show(); });
}

MainWindow::~MainWindow()
{
}

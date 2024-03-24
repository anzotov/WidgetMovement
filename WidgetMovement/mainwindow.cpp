#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    resize(300, 600);
    m_timer = new QTimer(this);
    m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, [this]() {
                constexpr auto buttonSize = QSize(10, 10);
                constexpr auto minIntervalMs = 100, maxIntervalMs = 1000;
                this->m_timer->setInterval(QRandomGenerator::global()->bounded(minIntervalMs, maxIntervalMs));
                auto button = new QPushButton(this);
                auto windowSize = this->size();
                auto position = QPoint(QRandomGenerator::global()->bounded(0, windowSize.width() - buttonSize.width()), 100);
                button->setGeometry(QRect(position, buttonSize));
                button->show();
                auto buttonTimer = new QTimer(button);
                buttonTimer->setInterval(20);
                connect(buttonTimer, &QTimer::timeout, button, [button](){
                    constexpr auto movement = QPoint(0, 1);
                    button->move(button->pos()+movement);
                    if(!button->parentWidget()->contentsRect().contains(button->geometry())) {
                        button->deleteLater();
                    }
                    }); 
                buttonTimer->start(); });
}

MainWindow::~MainWindow()
{
}

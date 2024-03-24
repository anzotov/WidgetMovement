#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    resize(300, 600);
    grabKeyboard();
    m_timer = new QTimer(this);
    m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, [this]() {
                constexpr auto buttonSize = QSize(10, 10);
                constexpr auto minCreateInvlMs = 100, maxInvlMs = 1000;
                constexpr auto minMoveInvlMs = 15, maxMoveInvlMs = 30;
                this->m_timer->setInterval(QRandomGenerator::global()->bounded(minCreateInvlMs, maxInvlMs));
                auto button = new QPushButton(this);
                auto windowSize = this->size();
                auto position = QPoint(QRandomGenerator::global()->bounded(0, windowSize.width() - buttonSize.width()), 100);
                button->setGeometry(QRect(position, buttonSize));
                button->show();
                auto buttonTimer = new QTimer(button);
                auto moveInterval = QRandomGenerator::global()->bounded(minMoveInvlMs, maxMoveInvlMs);
                buttonTimer->setInterval(moveInterval);
                connect(buttonTimer, &QTimer::timeout, button, [button](){
                    constexpr auto movement = QPoint(0, 1);
                    button->move(button->pos()+movement);
                    if(!button->parentWidget()->contentsRect().contains(button->geometry())) {
                        button->deleteLater();
                    }
                    }); 
                connect(button, &QPushButton::clicked, button, [button](){
                    button->deleteLater();});
                buttonTimer->start(); });
}

MainWindow::~MainWindow()
{
}

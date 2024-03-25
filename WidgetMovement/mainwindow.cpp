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
    constexpr auto minCreationTimeMs = 100, maxCreationTimeMs = 1000;
    connect(m_timer, &QTimer::timeout, this, [this, minCreationTimeMs, maxCreationTimeMs]() {
                m_timer->setInterval(QRandomGenerator::global()->bounded(minCreationTimeMs, maxCreationTimeMs));

                auto button = new QPushButton(this);
                constexpr auto buttonSize = QSize(15, 15);
                const auto buttonPos = QPoint(
                    QRandomGenerator::global()->bounded(0, size().width() - buttonSize.width()), 
                    QRandomGenerator::global()->bounded(0, 100 - buttonSize.height())
                );
                button->setGeometry(QRect(buttonPos, buttonSize));
                button->setText("*");
                button->show();

                auto buttonTimer = new QTimer(button);
                connect(buttonTimer, &QTimer::timeout, button, [button](){
                    auto movement = button->underMouse()?QPoint(0, 2):QPoint(0, 1);
                    button->move(button->pos()+movement);

                    if(!button->parentWidget()->contentsRect().contains(button->geometry())) {
                        button->deleteLater();
                    }

                    if(button->geometry().bottom() >= button->parentWidget()->contentsRect().bottom())
                    {
                        button->parentWidget()->setWindowTitle("Вы проиграли!");
                        button->parentWidget()->setStyleSheet("QMainWindow { background: red }");
                    }
                    }); 

                connect(button, &QPushButton::pressed, button, [button](){
                    button->deleteLater();});

                buttonTimer->start(QRandomGenerator::global()->bounded(15, 30)); });
    m_timer->start(QRandomGenerator::global()->bounded(minCreationTimeMs, maxCreationTimeMs));
}

MainWindow::~MainWindow()
{
}

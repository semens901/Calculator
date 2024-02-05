#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QPushButton *> allButtons = findChildren<QPushButton *>();

    // Соединяем сигнал pressed каждой кнопки с общим слотом
    for (QPushButton *button : allButtons) {
        connect(button, &QPushButton::pressed, this, &MainWindow::btn_handler);
    }

    //connect(ui->btn_addition, &QAbstractButton::pressed, this, &MainWindow::btn_handler);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_handler()
{
    QAbstractButton *button = qobject_cast<QAbstractButton*>(sender());
    if (button)
    {
        qDebug() << "Нажата кнопка:" << button->text();
    }
}

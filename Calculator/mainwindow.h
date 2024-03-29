#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QAbstractButton>
#include <QDebug>
#include<QMessageBox>
#include<QString>
#include<muParser.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    mu::Parser calculator;

private slots:
    void btn_handler();
};
#endif // MAINWINDOW_H

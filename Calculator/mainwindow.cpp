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
        QString operations_text = ui->window_operations->text();
        char last_symbol = operations_text[operations_text.size()-1].toLatin1();
        char symbol = button->text()[0].toLatin1();
        QString button_text = button->text().toLatin1();
        if(button_text == "+/-")
        {
            if(operations_text[0] == "-")
            {
                operations_text.remove(0, 1);
                ui->window_operations->setText(operations_text);
                return;
            }
            if(operations_text == "Error")
            {
                ui->window_operations->clear();
                operations_text.clear();
                operations_text = "0";
            }
            ui->window_operations->setText('-' + operations_text);
            return;
        }
        if((symbol >= '0') && (symbol <= '9'))
        {
            if(operations_text[0] == '0')
            {
                ui->window_operations->clear();
                operations_text.clear();
            }

            if(operations_text == "Error")
            {
                ui->window_operations->clear();
                operations_text.clear();
            }
            ui->window_operations->setText(operations_text + symbol);
        }
        else if((symbol >= '(') && (symbol <= '/'))
        {
            if(operations_text == "Error")
                return;
            switch(symbol)
            {
            case '+':
                if(!((last_symbol >= '*') && (last_symbol <= '/'))  && (last_symbol != 'r'))
                {
                    ui->window_operations->setText(operations_text + symbol);
                }
                else if(((last_symbol >= '*') && (last_symbol <= '/'))  && (last_symbol != 'r'))
                {
                    operations_text[operations_text.size() - 1] = symbol;
                    ui->window_operations->setText(operations_text);
                }
                break;
            case '-':
                if(operations_text[0] == '0' || (last_symbol == 'r'))
                {
                    ui->window_operations->clear();
                    operations_text.clear();
                    ui->window_operations->setText(operations_text + symbol);
                    break;
                }
                if(!((last_symbol >= '*') && (last_symbol <= '/')))
                {
                    ui->window_operations->setText(operations_text + symbol);
                }
                else if(((last_symbol >= '*') && (last_symbol <= '/')))
                {
                    operations_text[operations_text.size() - 1] = symbol;
                    ui->window_operations->setText(operations_text);
                }
                break;
            case '*':
                if(!((last_symbol >= '*') && (last_symbol <= '/')) && (last_symbol != 'r'))
                {
                    ui->window_operations->setText(operations_text + symbol);
                }
                else if(((last_symbol >= '*') && (last_symbol <= '/'))  && (last_symbol != 'r'))
                {
                    operations_text[operations_text.size() - 1] = symbol;
                    ui->window_operations->setText(operations_text);
                }
                break;
            case '/':
                if(!((last_symbol >= '*') && (last_symbol <= '/')) && (last_symbol != 'r'))
                {
                    ui->window_operations->setText(operations_text + symbol);
                }
                else if(((last_symbol >= '*') && (last_symbol <= '/'))  && (last_symbol != 'r'))
                {
                    operations_text[operations_text.size() - 1] = symbol;
                    ui->window_operations->setText(operations_text);
                }
                break;
            case '(':
                if(operations_text[0] == '0' && (last_symbol != 'r'))
                {
                    ui->window_operations->clear();
                    operations_text.clear();
                    ui->window_operations->setText(operations_text + symbol);
                    break;
                }
                if((last_symbol != ')') && (last_symbol < '0') && (last_symbol != ',')  && (last_symbol != 'r'))
                    ui->window_operations->setText(operations_text + symbol);
                break;
            case ')':
                if(!operations_text.contains('(') && (last_symbol != 'r'))
                    break;
                if(!((last_symbol >= '*') && (last_symbol <= '/'))  && (last_symbol != 'r'))
                    ui->window_operations->setText(operations_text + symbol);
                if(last_symbol == ')')
                    ui->window_operations->setText(operations_text + symbol);
                break;
            case ',':
                if(!((last_symbol >= '*') && (last_symbol <= '/')))
                    ui->window_operations->setText(operations_text + symbol);
                break;
            }
        }
        else if(symbol == '=')
        {
            calculator.SetExpr(operations_text.toStdString());
            calculator.SetDecSep(',');
            calculator.SetArgSep('.');
            try {
                double result = calculator.Eval();
                ui->window_operations->setText(QString::number(result));
            } catch (mu::Parser::exception_type &e) {
                ui->window_operations->setText(QString::fromUtf8("Error"));
            }
        }
        else if(symbol == 'C')
        {
            ui->window_operations->clear();
            ui->window_operations->setText("0");

        }
        else if(symbol == 'A')
        {
            ui->window_operations->clear();
            ui->window_operations->setText("0");
        }
        /*QMessageBox msgBox;
        msgBox.setText(QString(QChar::fromLatin1(symbol)));
        msgBox.exec();*/
    }
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QPointer>
#include <QPen>
#include <QTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->birthday_date->setDate(QDate::currentDate());
    ui->current_date->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

int days = 0;

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Инфо", "Биоритм - это явления в жизни любого живого организма, "
    "которые имеют циклическую природу и определённые закономерности."
    " У человека три графика биоритмов: физический, эмоциональный и интеллектуальный.");
}


void MainWindow::paintEvent(QPaintEvent* ){
    days = /*abs(*/ui->current_date->date().toJulianDay() - ui->birthday_date->date().toJulianDay()/*)*/;
    ui->days->setText("Количество прожитых дней: " + QString::number(days));

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    ui->result_label->setText("Физиологический (красный):\t" + QString::number(sin(2*days*M_PI/23)*100) +
    "\nЭмоциональный (синий):\t" + QString::number(sin(2*days*M_PI/28)*100) +
    "\nИнтеллектуальный (зелёный):\t" + QString::number(sin(2*days*M_PI/33)*100));

    painter.translate(width()/2, height()/2 + 100);
    painter.drawLine(-width()/2, 0, width()/2, 0);
    painter.drawLine(0, -100, 0, 100);
    painter.drawLine(-width(), 100, width(), 100);
    painter.drawLine(-width(), -100, width(), -100);

    QPoint point;
    painter.save();
    for (double j = -width()/60, i = -width() / 60; i <= width() / 60; i += 0.01, j += 0.01)
    {
        point.setX(j*30);
        double x = 0;

        QPen linepen(Qt::red);
        linepen.setWidth(3);
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/23)*100);
        painter.drawPoint(point);

        linepen.setColor(Qt::blue);
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/28)*100);
        painter.drawPoint(point);

        linepen.setColor(Qt::green);
        painter.setPen(linepen);
        point.setY(sin(-(i+days)*2*M_PI/33)*100);
        painter.drawPoint(point);
    }
    painter.restore();

    for (int j=-width()/60; j <= width()/60; j++)
    {
        if (j == 0)
        {
            painter.save();
            QPen linepen(Qt::black);
            linepen.setWidth(3);
            painter.setPen(linepen);
            painter.drawLine(0, -20, 0, 20);


            painter.rotate(90);
            QString date = ui->current_date->date().addDays(-j).toString();
            painter.drawText(10, j*30, date);
            painter.restore();
        }
        else
        {
            painter.drawLine(j*30, -10, j*30, 10);
            painter.save();

            painter.rotate(90);
            QString date = ui->current_date->date().addDays(-j).toString();
            painter.drawText(10, j*30, date);
            painter.restore();
        }
    }


    painter.end();
    update();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            int Days = ui->birthday_date->date().daysTo(ui->current_date->date());
            QTextStream out(&file);
            out << "Birthday day is " << ui->birthday_date->date().toString("dd.MM.yyyy") << Qt::endl;
            out << "Current day is " << ui->current_date->date().toString("dd.MM.yyyy") << Qt::endl;
            out << "Number of days " << abs(Days);
            file.close();
        }
        else
        {
            QMessageBox::information(this, "Error", "Could not save the file");
        }
    }
    else
    {
        QMessageBox::information(this, tr("Information"), tr("Saving canceled"));
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Text Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty())
    {

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString line;
            while (!in.atEnd())
            {
                line = in.readLine();
                if (line.startsWith("Birthday day is "))
                {
                    ui->birthday_date->setDate(QDate::fromString(line.mid(16), "dd.MM.yyyy"));
                }
                else if (line.startsWith("Current day is "))
                {
                    ui->current_date->setDate(QDate::fromString(line.mid(15), "dd.MM.yyyy"));
                }
                else if (line.startsWith("Number of days "))
                {
                    int Days = line.mid(15).toInt();
                    ui->days->setText("Количество прожитых дней: " + QString::number(Days));
                }
            }
            file.close();
        }
    }
    else
        {
             QMessageBox::information(this, "Ошибка", "Не получается открыть файл");
        }

}


//21.12.2005 - 29.01.1959







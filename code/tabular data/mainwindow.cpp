#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStandardItemModel>
#include<QTableView>
#include<QString>
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

 //  QStandardItemModel* model=new QStandardItemModel(MyRows,MyColumns);
  //  ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(arg1.toInt())
    {
        int Cols=1;
        if(ui->lineEdit_2->text().toInt())
        {
            Cols=ui->lineEdit_2->text().toInt();
        }

      QStandardItemModel* model=new QStandardItemModel(arg1.toInt(),Cols);
            ui->tableView->setModel(model);
    }
}


void MainWindow::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(arg1.toInt())
    {
        int Rows=1;
        if(ui->lineEdit->text().toInt())
        {
            Rows=ui->lineEdit->text().toInt();
        }

       QStandardItemModel* model=new QStandardItemModel(Rows,arg1.toInt());
            ui->tableView->setModel(model);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString filename("C:/Users/New/Downloads/MyTables/Table_APL.xlsx");
    QAxObject* excel=new QAxObject("Excel.Application",this);
    QAxObject* workbooks = excel->querySubObject("Workbooks"); // рабочая книга Bb
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", filename);
    excel->dynamicCall("SetVisible(bool)",false); // видимость документа

    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);//Ss

    //получаем кол-во используемых строк и столбцов
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");//Rr
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");

    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();

    QStandardItemModel* model=new QStandardItemModel(intRows,intCols);


    for (int row=0; row<intRows; row++)
    {
        for(int col=0; col<intCols; col++)
        {
            QAxObject* cell = worksheet->querySubObject("Cells(int,int)", row+1, col+1);
            QVariant value = cell->dynamicCall("Value()");
            model->setItem(row,col, new QStandardItem(value.toString()));
        }
    }
   ui->tableView->setModel(model);
    //workbook->setProperty("Saved", "True");
    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");

}



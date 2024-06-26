#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPaintEvent>
#include <QDate>
#include <QMainWindow>

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

private slots:
    void on_actionAbout_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*) override;
};
#endif // MAINWINDOW_H

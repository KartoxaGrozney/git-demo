#include "qmyform.h"
#include "qworkform.h"
#include <QMenu>
#include <QtWidgets>

QMyForm::QMyForm(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu* file = new QMenu("&File");
    QMenu* info = new QMenu("&Info");
    QWorkForm* form = new QWorkForm;

    file->addAction("&Open", form, SLOT(slotLoad()));
    info->addAction("&Help", this, SLOT(slotInfo()));
    file->addAction("&Save", form, SLOT(slotSave()));
    file->addAction("&Save as", form, SLOT(slotSaveAs()));
    file->addSeparator();
    file->addAction("&Quit", qApp, SLOT(quit()));

    menuBar()->addMenu(file);
    menuBar()->addMenu(info);
    statusBar()->setVisible(false);
    setCentralWidget(form);
    connect(form, SIGNAL(ChangeTitle(const QString&)), SLOT(slotChangeTitle(const QString&)));
}

QMyForm::~QMyForm() {}

void QMyForm::slotInfo()
{
    QMessageBox::about(this, "Abuot", "This is SDI-application - notepad");
}

void QMyForm::slotChangeTitle(const QString& str)
{
    this->setWindowTitle(str);
}

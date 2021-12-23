#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dial.h"
#include "QHBoxLayout"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Dial *d = new Dial();
    d->setRange(0,240);
    d->setCurrentValue(180);
    d->update();
    QHBoxLayout* l = new QHBoxLayout();
    l->addWidget(d);
    ui->centralWidget->setLayout(l);
}

MainWindow::~MainWindow()
{
    delete ui;
}

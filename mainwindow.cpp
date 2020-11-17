#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    my_solver->InitSPH();
    ui->openGLWidget->setVector(&(my_solver->particles));


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(haha()));
    timer->start(40);

}

void MainWindow::haha()
{
    my_solver->Update();
    ui->openGLWidget->setVector(&(my_solver->particles));
}

MainWindow::~MainWindow()
{
    delete ui;
}


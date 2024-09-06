#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->hide();

    clock_lab_ = new QLabel(this);
    setCentralWidget(clock_lab_);
    clock_lab_->setMaximumHeight(400);
    clock_lab_->setMaximumWidth(400);
    clock_lab_->setMinimumHeight(400);
    clock_lab_->setMinimumWidth(400);

    setMaximumHeight(400);
    setMaximumWidth(400);
    setMinimumHeight(400);
    setMinimumWidth(400);

    this->setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pix(400,400);
    clock_lab_->setPixmap(pix);



}

void MainWindow::set_clock_pixmap(const QPixmap &pixmap) const {
    clock_lab_->setPixmap(pixmap);
}

MainWindow::~MainWindow() {
    delete ui;
}

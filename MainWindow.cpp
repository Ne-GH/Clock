#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <iostream>


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

    // setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnBottomHint);

    clock_img_.set_width_height(width(), height());

}

MainWindow::~MainWindow() {
    delete ui;
}


/*
QPixmap MainWindow::draw_pixmap(const Time &time) {
    /*
    auto hour_angle = time.hour() * 15;  // hour / 24 * 360
    auto minute_angle = time.minute() * 6; // minute / 60 * 360
    int second_angle = time.second() * 6; // second / 60 * 360
    auto millisecond_angle = time.millisecond() * 0.006; // millisecond / 1000 * 6 (1毫秒占6度)

    QPixmap pixmap(width(),height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen(Qt::black);
    pen.setWidth(40);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法

    painter.end();
    #1#



    return pixmap;
}*/
void MainWindow::update_clock() {
    clock_img_.draw_pixmap();
    clock_lab_->setPixmap(clock_img_.pixmap());
    // clock_lab_->setPixmap(draw_pixmap(Time()));
}

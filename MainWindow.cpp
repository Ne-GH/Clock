﻿#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <iostream>

#include "ColorChooseWidget.h"

#include <QColor>
#include <QDataStream>
#include <QFile>

// 重载 QDataStream 操作符
QDataStream& operator<<(QDataStream& out, const ClockColor& color) {
    out << color.second_color << color.minute_color << color.hour_color;
    return out;
}

QDataStream& operator>>(QDataStream& in, ClockColor& color) {
    in >> color.second_color >> color.minute_color >> color.hour_color;
    return in;
}

QDataStream& operator<<(QDataStream& out, const QPen& pen) {
    out << pen.width();
    return out;
}

QDataStream& operator>>(QDataStream& in, QPen& pen) {
    int width;
    in >> width;
    pen.setWidth(width);
    return in;
}

// 序列化
void MainWindow::save(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << clock_color_;
        out << clock_image_->pen_;
        out << is_24;
        file.close();
    }
}

// 反序列化
void MainWindow::load(const QString& filename) {
    QFile file(filename);
    ClockColor color;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        // color
        in >> color;

        // pen
        QPen pen;
        in >> pen;
        int width = pen.width();
        if (width == 0) {
            width = 40;
        }
        clock_image_->set_pen_width(width);
        clock_color_ = color;

        // 进制
        in >> is_24;


        file.close();
    }

}



Menu::Menu(QMainWindow *parent = nullptr) {
    menu_ = std::make_unique<QMenu>();
    quit_action_ = std::make_unique<QAction>("退出");
    color_choose_action_ = std::make_unique<QAction>("调色板");
    color_choose_widget_ = std::make_unique<ColorChooseWidget>();

    menu_->addAction(color_choose_action_.get());
    menu_->addAction(quit_action_.get());

    QObject::connect(quit_action_.get(), &QAction::triggered, [] {
        exit(0);
    });


    QObject::connect(color_choose_action_.get(), &QAction::triggered, [=] {
        if (parent == nullptr)
            return;
        auto window = dynamic_cast<MainWindow *>(parent);

        QObject::connect(color_choose_widget_.get(),&ColorChooseWidget::change_color,[=](ClockColor clock_color) {
            window->clock_color_ = clock_color;
            color_choose_widget_->draw_lab_color(clock_color);
            window->save("./config.cfg");

        });
        QObject::connect(color_choose_widget_.get(),&ColorChooseWidget::change_pen_width,[=](int pen_width) {
            window->clock_image_->set_pen_width(pen_width);
            window->save("./config.cfg");

        });
        QObject::connect(color_choose_widget_.get(),&ColorChooseWidget::change_base_to_24,[=](bool is_24) {
            window->is_24 = is_24;

            window->save("./config.cfg");

        });
        const auto clocks = window->clock_color_;
        color_choose_widget_->draw_lab_color({clocks.second_color,clocks.minute_color,clocks.hour_color});
        color_choose_widget_->set_pen_lan_value(window->clock_image_->pen_.width());
        color_choose_widget_->draw_checkbox(window->is_24);
        color_choose_widget_->exec();

    });


}

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

    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);


    clock_image_ = std::make_unique<ClockImage>(width(),height());
    clock_image_->draw_pixmap(is_24);

    tray_icon_.setIcon(clock_image_->pixmap());
    tray_icon_.setToolTip("Clock");
    tray_icon_.show();
    menu_ = std::make_unique<Menu>(this);

    tray_icon_.setContextMenu(menu_->menu());
    load("./config.cfg");

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::update_clock() {
    clock_image_->set_color(clock_color_);
    clock_image_->draw_pixmap(is_24);
    clock_lab_->setPixmap(clock_image_->pixmap());
    tray_icon_.setIcon(clock_image_->pixmap());
}


QMenu *Menu::menu(){
    return menu_.get();
}

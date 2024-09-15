#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <iostream>

#include "ColorChooseWidget.h"

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

        QObject::connect(color_choose_widget_.get(),&ColorChooseWidget::change_color,[=](ClockColor clock_color) {
            dynamic_cast<MainWindow *>(parent)->clock_color_ = clock_color;
            color_choose_widget_->draw_lab_color(clock_color);
        });
        QObject::connect(color_choose_widget_.get(),&ColorChooseWidget::change_pen_width,[=](int pen_width) {
            auto main_window = dynamic_cast<MainWindow *>(parent);
            auto pen = main_window->clock_image_->pen_;
            pen.setWidth(pen_width);
            main_window->clock_image_->pen_ = pen;
            main_window->clock_image_->painter_->setPen(pen);

        });

        const auto clocks = dynamic_cast<MainWindow *>(parent)->clock_color_;
        color_choose_widget_->draw_lab_color({clocks.second_color,clocks.minute_color,clocks.hour_color});
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
    clock_image_->draw_pixmap();

    tray_icon_.setIcon(clock_image_->pixmap());
    tray_icon_.setToolTip("Clock");
    tray_icon_.show();
    menu_ = std::make_unique<Menu>(this);

    tray_icon_.setContextMenu(menu_->menu());

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::update_clock() {
    clock_image_->set_color(clock_color_);
    clock_image_->draw_pixmap();
    clock_lab_->setPixmap(clock_image_->pixmap());
    tray_icon_.setIcon(clock_image_->pixmap());
}

QMenu *Menu::menu(){
    return menu_.get();
}

/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 17:32
*******************************************************************************/

#include "ColorChooseWidget.h"

#include "MainWindow.h"
#include "ui_ColorChooseWidget.h"
#include <QColorDialog>


ColorChooseWidget::ColorChooseWidget(QWidget *parent) :
    QDialog(parent), ui(new Ui::ColorChooseWidget) {
    ui->setupUi(this);

    QObject::connect(ui->second_color_but,&QPushButton::clicked,[=] {
        emit change_color({QColorDialog::getColor(),
            ui->minute_color_lab->palette().window().color(),
            ui->hour_color_lab->palette().window().color()});
    });

    QObject::connect(ui->minute_color_but,&QPushButton::clicked,[=] {
        emit change_color({ui->second_color_lab->palette().window().color(),
            QColorDialog::getColor(),
            ui->hour_color_lab->palette().window().color()});
    });

    QObject::connect(ui->hour_color_but,&QPushButton::clicked,[=] {
        emit change_color({ui->second_color_lab->palette().window().color(),
            ui->minute_color_lab->palette().window().color(),
            QColorDialog::getColor()});
    });

    QObject::connect(ui->pen_width,&QSlider::valueChanged,[=] {
        emit change_pen_width(ui->pen_width->value());
    });

    QObject::connect(ui->check_12, &QCheckBox::clicked,[=] {
        ui->check_12->setChecked(true);
        ui->check_24->setChecked(false);
        emit change_base_to_24(false);
    });
    QObject::connect(ui->check_24, &QCheckBox::clicked,[=] {
        ui->check_24->setChecked(true);
        ui->check_12->setChecked(false);
        emit change_base_to_24(true);
    });

}

void ColorChooseWidget::draw_lab_color(const ClockColor color) const {
    QPalette palette;
    palette.setColor(QPalette::Window, color.second_color);
    ui->second_color_lab->setAutoFillBackground(true);
    ui->second_color_lab->setPalette(palette);



    palette.setColor(QPalette::Window, color.minute_color);
    ui->minute_color_lab->setAutoFillBackground(true);
    ui->minute_color_lab->setPalette(palette);



    palette.setColor(QPalette::Window, color.hour_color);
    ui->hour_color_lab->setAutoFillBackground(true);
    ui->hour_color_lab->setPalette(palette);
}
void ColorChooseWidget::set_pen_lan_value(const int val) {
    ui->pen_width->setValue(val);
}
void ColorChooseWidget::draw_checkbox(bool is_24) {
    if (is_24 == true) {
        ui->check_24->setChecked(true);
        ui->check_12->setChecked(false);
    }
    else {
        ui->check_24->setChecked(false);
        ui->check_12->setChecked(true);
    }
}

ColorChooseWidget::~ColorChooseWidget() { delete ui; }

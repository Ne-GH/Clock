/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 10:10
*******************************************************************************/

#pragma once
#include "Time.h"
#include <QPainter>

class ClockImage {
    QPainter painter_;
    QPixmap pixmap_;

    QColor hour_color_;
    QColor minute_color_;
    QColor second_color_;

public:
    ClockImage();

    void draw_round(int radius, int angle);

    void set_width_height(int,int);

    void draw_pixmap();

    const QPixmap& pixmap();

    void set_color(QColor, QColor, QColor);

    ~ClockImage();


};

/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 10:10
*******************************************************************************/

#pragma once
#include <QPainter>
#include <new>
#include "Time.h"

#include "ColorChooseWidget.h"

class ClockImage {
    std::unique_ptr<QPainter> painter_;
    std::unique_ptr<QPainter> scale_painter_;
    std::unique_ptr<QPixmap> pixmap_;

    friend class Menu;
    friend class MainWindow;
    QPen pen_;


    ClockColor color_;

public:
    ClockImage(int, int);
    void painter_draw(bool is_24);

    void scale_painter_draw(bool is_24);

    void draw_round(int radius, int angle);

    void draw_pixmap(bool);

    void set_pen_width(int);

    const QPixmap& pixmap();

    void set_color(ClockColor);

    ~ClockImage();


};

/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 10:10
*******************************************************************************/


#include "ClockImage.h"

ClockImage::ClockImage() = default;

void ClockImage::set_width_height(const int width, const int height) {
    pixmap_ = QPixmap(width,height);
    painter_.begin(&pixmap_);
    QPen pen;
    pen.setWidth(40);
    pen.setCapStyle(Qt::FlatCap);
    painter_.setPen(pen);
    painter_.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
}

void ClockImage::draw_round(int radius, int angle) {
    const auto pen_width = painter_.pen().width();
    const int begin_pos = static_cast<int>(pixmap_.width() * 0.5 - radius + 0.5 * pen_width);
    const int width = radius * 2 - pen_width;
    const int height = radius * 2 - pen_width;

    painter_.drawArc(begin_pos,begin_pos,
                    width, height,
                    90 * 16 , -(angle) * 16);

}

void ClockImage::draw_pixmap() {

    const Time time;
    pixmap_.fill(Qt::transparent);

    auto hour = time.hour() * 15;  // hour / 24 * 360
    auto minute = time.minute() * 6; // minute / 60 * 360
    int second = time.second() * 6; // second / 60 * 360
    auto millisecond = time.millisecond() * 0.006; // millisecond / 1000 * 6 (1毫秒占6度)

    draw_round(pixmap_.width()/2 , second);
    draw_round(pixmap_.width()/2 - painter_.pen().width() , minute);
    draw_round(pixmap_.width()/2 - painter_.pen().width() * 2, hour);




}

const QPixmap &ClockImage::pixmap() {
    return pixmap_;
}

void ClockImage::set_color(QColor hour_color, QColor minute_color, QColor second_color) {
    hour_color_ = hour_color;
    minute_color_ = minute_color;
    second_color_ = second_color;
}

ClockImage::~ClockImage(){
    painter_.end();

}


/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 10:10
*******************************************************************************/

#include "ClockImage.h"

ClockImage::ClockImage(int width,int height) {
    pixmap_ = std::make_unique<QPixmap>(width,height);
    painter_ = std::make_unique<QPainter>(pixmap_.get());

    pen_.setWidth(40);
    pen_.setCapStyle(Qt::FlatCap);
    painter_->setPen(pen_);
    painter_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
}
void ClockImage::set_pen_width(const int pen_width) {
    auto pen = pen_;
    pen.setWidth(pen_width);
    pen_ = pen;
    painter_->setPen(pen_);
}


void ClockImage::draw_round(int radius, int angle) {
    const auto pen_width = painter_->pen().width();
    const int begin_pos = std::floor(pixmap_->width() * 0.5 - radius + 0.5 * pen_width);
    const int width = std::floor(radius * 2 - pen_width);
    const int height = std::floor(radius * 2 - pen_width);

    painter_->drawArc(begin_pos,begin_pos,
                    width, height,
                    90 * 16, -(angle) * 16);
}


void ClockImage::draw_pixmap(bool is_24) {

    const Time time;
    pixmap_->fill(Qt::transparent);

    int second,minute,hour,millisecond;
    if (is_24)
        hour = time.hour() * 15;  // hour / 24 * 360
    else
        hour = (time.hour() - 12) * 30;  // hour / 12 * 360

    minute = time.minute() * 6; // minute / 60 * 360
    second = time.second() * 6; // second / 60 * 360

    pen_.setColor(color_.second_color);
    painter_->setPen(pen_);
    draw_round(pixmap_->width()/2 , second);

    pen_.setColor(color_.minute_color);
    painter_->setPen(pen_);
    draw_round(pixmap_->width()/2 - painter_->pen().width() , minute);

    pen_.setColor(color_.hour_color);
    painter_->setPen(pen_);
    draw_round(pixmap_->width()/2 - painter_->pen().width() * 2, hour);

}

const QPixmap &ClockImage::pixmap() {
    return *pixmap_;
}

void ClockImage::set_color(ClockColor clock_color) {
    color_ = clock_color;
}

ClockImage::~ClockImage(){
    painter_->end();

}


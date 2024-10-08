/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 10:10
*******************************************************************************/

#include "ClockImage.h"

ClockImage::ClockImage(int width,int height) {
    pixmap_ = std::make_unique<QPixmap>(width,height);
    painter_ = std::make_unique<QPainter>();
    scale_painter_ = std::make_unique<QPainter>();
    scale_pen_ = QPen(Qt::black);

    scale_pen_.setWidth(5);
    scale_pen_.setCapStyle(Qt::FlatCap);


}
void ClockImage::painter_draw(bool is_24) {

    painter_->begin(pixmap_.get());
    pen_.setCapStyle(Qt::FlatCap);
    painter_->setPen(pen_);
    painter_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法

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

    painter_->end();
}

void ClockImage::scale_painter_draw(bool is_24){
    int width = pixmap_->width();
    int height = pixmap_->height();
    int pen_width = pen_.width();
    scale_painter_->begin(pixmap_.get());
    scale_painter_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    scale_painter_->save();
    scale_painter_->translate(pixmap_->width()/2,pixmap_->height()/2);
    auto scale_line = QLine(0,height/2 - pen_width / 4,0,height/2);
    auto big_scale_line = QLine(0,height/2 - pen_width / 2,0,height/2);

    scale_pen_.setWidth(3);
    scale_painter_->setPen(scale_pen_);
    for (int i = 0;i < 360; i += 6) {
        scale_painter_->rotate(6);
        scale_painter_->drawLine(scale_line);
    }

    scale_pen_.setWidth(6);
    scale_painter_->setPen(scale_pen_);
    for (int i = 0;i < 360; i += 30) {
        scale_painter_->rotate(30);
        scale_painter_->drawLine(big_scale_line);
    }

    scale_painter_->restore();
    scale_painter_->end();

}

void ClockImage::set_pen_width(const int pen_width) {
    pen_.setWidth(pen_width);
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

    painter_draw(is_24);

    scale_painter_draw(is_24);
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


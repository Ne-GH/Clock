/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/09/14 17:32
*******************************************************************************/


#pragma once

#include <QDialog>


struct ClockColor {
    QColor second_color = Qt::black;
    QColor minute_color = Qt::black;
    QColor hour_color = Qt::black;
};

QT_BEGIN_NAMESPACE
namespace Ui { class ColorChooseWidget; }
QT_END_NAMESPACE

class ColorChooseWidget : public QDialog {
Q_OBJECT

public:
    explicit ColorChooseWidget(QWidget *parent = nullptr);
    ~ColorChooseWidget() override;
    void draw_lab_color(const ClockColor) const;
    void set_pen_lan_value(int);
    void draw_checkbox(bool);

signals:
    void change_color(ClockColor);
    void change_pen_width(int);
    void change_base_to_24(bool);
private:
    Ui::ColorChooseWidget *ui;
};


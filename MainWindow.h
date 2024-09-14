#pragma once

#include <QMainWindow>
#include <QLabel>
#include "Time.h"
#include "ClockImage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    QLabel *clock_lab_;
    ClockImage clock_img_;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void update_clock();

};

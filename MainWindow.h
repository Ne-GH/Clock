#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "ClockImage.h"
#include "Time.h"

#include "ColorChooseWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class Menu {
    std::unique_ptr<QMenu> menu_;
    std::unique_ptr<QAction> quit_action_;
    std::unique_ptr<QAction> color_choose_action_;
    std::unique_ptr<ColorChooseWidget> color_choose_widget_;
public:
    explicit Menu(QMainWindow *);
    QMenu *menu();

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class Menu;

    Ui::MainWindow *ui;
    QLabel *clock_lab_;
    std::unique_ptr<ClockImage> clock_image_;
    QSystemTrayIcon tray_icon_;
    ClockColor clock_color_;
    std::unique_ptr<Menu> menu_;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void update_clock();

};



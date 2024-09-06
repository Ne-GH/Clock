#pragma once

#include <QMainWindow>
#include <QLabel>

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
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void set_clock_pixmap(const QPixmap &) const;

};

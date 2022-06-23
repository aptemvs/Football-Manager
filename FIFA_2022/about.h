#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QPainter>

namespace Ui
{
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget* parent = nullptr);

    ~About();

private:
    Ui::About* ui;

    void paintEvent(QPaintEvent* event);
};

#endif // ABOUT_H

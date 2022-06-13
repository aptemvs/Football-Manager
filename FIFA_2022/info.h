#ifndef INFO_H
#define INFO_H

#include <QDialog>

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

public:
    void setData(QString name, int number);

private:
    Ui::Info *ui;
};

#endif // INFO_H

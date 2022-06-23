#ifndef ADDROW_H
#define ADDROW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui
{
class addRow;
}

class addRow : public QDialog
{
    Q_OBJECT

public:
    explicit addRow(QWidget* parent = nullptr);
    ~addRow();

public:
    const QList <QVariant>& getNewRow();

private:
    QList <QVariant> newRow;
    Ui::addRow* ui;

private
    slots:
    void saveAddedRow();
};

#endif    // ADDROW_H

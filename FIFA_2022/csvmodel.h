#ifndef CSVMODEL_H
#define CSVMODEL_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QAbstractTableModel>

class csvModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit csvModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant getData(size_t row, size_t column) const;

    QList<QVariant> getValues(size_t index);

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void fillDataTableFromFile(const QString path);

    void appendRow(const QList<QVariant> &row);

    void removeRow(const size_t numberOfRow);

    void exportFile(const QString path);

private:
    QList<QList<QVariant>> dataTable;
    QList<QVariant> headerList;
};

#endif // CSVMODEL_H

#ifndef CSVMODEL_H
#define CSVMODEL_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QItemSelection>
#include <QAbstractTableModel>
#include <QSet>
#include <QDate>
#include <QColor>

class CsvModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CsvModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant getData(size_t row, size_t column) const;

    QList <QVariant> getValues(size_t index);

    bool setData(const QModelIndex& index, const QVariant& value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void fillDataTableFromFile(const QString path);

    void appendRow(const QList <QVariant>& row);

    void removeRow(const size_t index);

    void exportFile(const QString& path);

    bool isRightData(const size_t col, QVariant& text);

    QSet<QString> getSet();

    void appendTeam(const QString& team);

private:
    QList <QList<QVariant>> dataTable;
    QList <QVariant> headerList;
    QSet <QString> footballTeams;

signals:
    void rowChanged();
};

#endif // CSVMODEL_H

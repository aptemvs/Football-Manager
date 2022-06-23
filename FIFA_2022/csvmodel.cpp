#include "csvmodel.h"

CsvModel::CsvModel(QObject* parent)
        : QAbstractTableModel(parent)
{
}

void CsvModel::fillDataTableFromFile(const QString path)
{
    dataTable.clear();
    headerList.clear();

    QFile inputFile(path);
    inputFile.open(QFile::ReadWrite | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString& item: firstline.split(","))
    {
        headerList.append(item);
    }

    while (!inputStream.atEnd())
    {           
        QString line = inputStream.readLine();
        QList <QVariant> dataRow;

        for (QString& item: line.split(","))
        {
            bool integer = true;
            if (item.toInt(&integer))
            {
                dataRow.append(item.toInt());
            } else
            {
                dataRow.append(item);
            }
        }
        footballTeams << dataRow[10].toString();
        dataTable.append(dataRow);
    }
    inputFile.close();
}

int CsvModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return dataTable.size();
}

int CsvModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    if (dataTable.empty())
    {
        return 0;
    }

    return dataTable[0].size();
}

QVariant CsvModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

QVariant CsvModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

QVariant CsvModel::getData(size_t row, size_t col) const
{
    return dataTable[row][col];
}

QList <QVariant> CsvModel::getValues(size_t index)
{
    return {dataTable[index][1], dataTable[index][3]};
}

bool CsvModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value)
    {
        int row = index.row();
        int col = index.column();
        QVariant newValue = value.value<QVariant>();

        if (isRightData(col, newValue))
        {
            dataTable[row][col] = newValue.toString();
            emit rowChanged();
            footballTeams.insert(value.toString());
            return true;
        }
     }
    return false;
}

Qt::ItemFlags CsvModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CsvModel::appendRow(const QList <QVariant>& row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    footballTeams.insert(row[10].toString());
    endInsertRows();
}

void CsvModel::removeRow(const size_t index)
{
    beginRemoveRows(QModelIndex(), index, index);
    dataTable.removeAt(index);
    endRemoveRows();
}

void CsvModel::exportFile(const QString& path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    bool first = true;
    for (QVariant& item: headerList)
    {
        if (first)
        {
            outputStream << item.toString();
            first = false;
        } else
        {
            outputStream << ",";
            outputStream << item.toString();
        }
    }
    outputStream << "\n";

    for (const QList <QVariant>& row: qAsConst(dataTable))
    {
        bool first = true;
        for (const QVariant& item: row)
        {
            if (first)
            {
                outputStream << item.toString();
                first = false;
            } else
            {
                outputStream << ",";
                outputStream << item.toString();
            }
        }
        outputStream << "\n";
    }
    outputFile.close();
}

bool CsvModel::isRightData(const size_t col, QVariant& text)
{
    if (col == 0 and text.userType() != QMetaType::QString)
    {
        QMessageBox::warning(NULL, "Warning", "Problem:\nName couldn't be string of digits / symbols");
        return false;
    } else if (col == 3 and (text.toInt() < 1 or text.toInt() > 101) and text.userType() == QMetaType::Int)
    {
        QMessageBox::warning(NULL, "Warning", "Insert the number from 1 to 100");
        return false;
    } else if (col == 4 and (text.toInt() < 1 or text.toInt() > 101))
    {
        QMessageBox::warning(NULL, "Warning", "Insert the number from 1 to 100");
        return false;
    } else if (col == 5)
    {
        QDate comp = QDate::fromString("1800-01-01", "yyyy-MM-dd");
        QDate test = QDate::fromString(text.value<QString>(), "yyyy-MM-dd");
        if (test < comp)
        {
            QMessageBox::warning(NULL, "Warning", "Wrong date format");
            return false;
        }
    } else if (col == 6 and text.toInt() < 20 or text.toInt() > 230)
    {
        QMessageBox::warning(NULL, "Warning", "Insert the number from 20 to 230");
        return false;
    }
    return true;
}

void CsvModel::appendTeam(const QString& team)
{
    footballTeams.insert(team);
}

QSet<QString> CsvModel::getSet()
{
    return footballTeams;
}

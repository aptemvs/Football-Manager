#pragma once
#include <QSet>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QStringListModel>
#include <QMessageBox>
#include <QComboBox>


class Delegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index);
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void fillFootballTeams(QSet<QString> temp);

private:
    QSet<QString> footballTeams;
};

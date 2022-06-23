#include "delegate.h"

Delegate::Delegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->setEditable(true);
    comboBox->blockSignals(false);

    for (const QString& team: qAsConst(footballTeams))
        comboBox->addItem(team);

    comboBox->model()->sort(0);

    return comboBox;
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)
{
    QComboBox *edit = qobject_cast<QComboBox*>(editor);

    model->setData(index, edit->currentText(), Qt::DisplayRole);
    model->setData(index, edit->itemData(edit->currentIndex()), Qt::UserRole);
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}

void Delegate::fillFootballTeams(QSet<QString> temp)
{
    footballTeams = temp;
}

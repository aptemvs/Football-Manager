#include "about.h"
#include "addrow.h"
#include "csvmodel.h"
#include "info.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _delegator = new Delegate(this);
    _csvModel = new CsvModel(this);
    _proxyModel = new QSortFilterProxyModel;

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setItemDelegateForColumn(10, _delegator);

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(ui->actionAdd_row, SIGNAL(triggered()), this, SLOT(addNewRow()));
    QObject::connect(ui->actionRemove_rows, SIGNAL(triggered()), this, SLOT(removeRows()));
    QObject::connect(ui->actionDetails, SIGNAL(triggered()), this, SLOT(showDetails()));
    QObject::connect(_csvModel, SIGNAL(rowChanged()), this, SLOT(fillTeams()));
}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");

    if (fileName != "")
    {
        _csvModel->fillDataTableFromFile(fileName);

        _proxyModel->invalidate(); // clear proxy model in case it is already filled with data

        _proxyModel->setSourceModel(_csvModel);

        ui->tableView->setModel(_proxyModel);

        fillTeams(); // fill the vector of teams for delegator

        std::vector<int> columnsToShow = {1, 3, 4, 5, 6, 10};

        for (int i = 0; i < _csvModel->columnCount(); i++)
        {
            if (std::find(columnsToShow.begin(), columnsToShow.end(), i) == columnsToShow.end())
            {
                ui->tableView->hideColumn(i);
            }
        }
    } else
    {
        QMessageBox::warning(this, "Warning", "Can't open the file\nPlease try again");
    }
}

void MainWindow::saveFile()
{
    if (_csvModel->rowCount() > 0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "../", "Data (*.csv)");

        if (fileName != "")
        {
            _csvModel->exportFile(fileName);
        } else
        {
            QMessageBox::warning(this, "Warning", "Can't export file\nDirectory wasn't selected");
        }

    } else
    {
        QMessageBox::warning(this, "Warning", "Can't export file\nThe file is not opened");
    }
}

void MainWindow::showAbout()
{
    hide();
    _windowAbout = new About(this);
    _windowAbout->exec();
    show();
}

void MainWindow::addNewRow()
{
    if (_csvModel->rowCount() > 0)
    {
        addRow window(this);

        if (window.exec() == QDialog::Accepted)
        {
            _csvModel->appendRow(window.getNewRow());
        }

    } else
    {
        QMessageBox::warning(this, "Warning", "Can't add row\nThe file is not opened");
    }
}

void MainWindow::removeRows()
{
    if (_csvModel->rowCount() > 0)
    {
        size_t previous = -1;
        QModelIndexList indexesOfRows = ui->tableView->selectionModel()->selection().indexes();
        QList<QModelIndex> realIndexesOfRows;

        for (const QModelIndex& item: qAsConst(indexesOfRows))
        {
            realIndexesOfRows.append(_proxyModel->mapToSource(item));
        }

        std::sort(realIndexesOfRows.begin(), realIndexesOfRows.end());
        std::reverse(realIndexesOfRows.begin(), realIndexesOfRows.end());

        for (const QModelIndex& index: qAsConst(realIndexesOfRows))
        {
            if (index.row() != previous)
            {
                _csvModel->removeRow(index.row());
                previous = index.row();
            }
        }
    } else
    {
        QMessageBox::warning(this, "Warning", "Can't remove row(s)\nThe file is not opened or row(s) not selected");
    }
}

void MainWindow::showDetails()
{
    if (_csvModel->rowCount() > 0)
    {
        size_t index = ui->tableView->currentIndex().row();
        QList <QVariant> values = _csvModel->getValues(index);

        Info windowInfo(this);
        windowInfo.setData(values[0].toString(), values[1].toInt());
        windowInfo.exec();
    } else
    {
        QMessageBox::warning(this, "Warning", "The row is not selected or more than one row is selected");
    }
}

void MainWindow::fillTeams()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid())
    {
        QString value = _csvModel->getData(index.row(), index.column()).toString();
        _csvModel->appendTeam(value);
        _delegator->fillFootballTeams(_csvModel->getSet());
    } else
    {
        _delegator->fillFootballTeams(_csvModel->getSet());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

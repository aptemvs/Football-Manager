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

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // stretch columns to same size

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(ui->actionAdd_row, SIGNAL(triggered()), this, SLOT(addNewRow()));
    QObject::connect(ui->actionRemove_row, SIGNAL(triggered()), this, SLOT(removeRow()));
    QObject::connect(ui->actionDetails, SIGNAL(triggered()), this, SLOT(showDetails()));
}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");

    if (fileName != "")
    {
        if (_csvModel)
        {
             delete _csvModel;
        }

        _csvModel = new csvModel(this);
        _csvModel->fillDataTableFromFile(fileName);

        proxyModel = new QSortFilterProxyModel;
        proxyModel->setSourceModel(_csvModel);

        ui->tableView->setModel(proxyModel);

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
        QMessageBox::warning(this, "Warning","Can't open the file\nPlease try again");
    }
}

void MainWindow::saveFile()
{
    if (_csvModel)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "../", "Data (*.csv)");

        if (fileName != "")
        {
            _csvModel->exportFile(fileName);
        } else
        {
            QMessageBox::warning(this, "Warning","Can't export file\nDirectory wasn't selected");
        }

    } else
    {
        QMessageBox::warning(this, "Warning","Can't export file\nThe file is not opened");
    }
}

void MainWindow::showAbout()
{
    hide();
    windowAbout = new About(this);
    windowAbout->exec();
    show();
}

void MainWindow::addNewRow()
{
    if (_csvModel)
    {
        addRow window(this);

        if (window.exec() == QDialog::Accepted)
        {
            _csvModel->appendRow(window.getNewRow());
        }

    } else
    {
        QMessageBox::warning(this, "Warning","Can't add row\nThe file is not opened");
    }
}

void MainWindow::removeRow()
{
    if (_csvModel)
    {
        size_t index = ui->tableView->currentIndex().row();
        _csvModel->removeRow(index);
    } else
    {
        QMessageBox::warning(this, "Warning","Can't remove row\nThe file is not opened or row is not selected");
    }
}

void MainWindow::showDetails()
{
    if (ui->tableView->currentIndex().isValid())
    {
        size_t index = ui->tableView->currentIndex().row();
        QList<QVariant> values = _csvModel->getValues(index);

        Info windowInfo (this);
        windowInfo.setData(values[0].toString(), values[1].toInt());
        windowInfo.exec();

    } else
    {
        QMessageBox::warning(this, "Warning","The row is not selected\nPlease select some row");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "about.h"
#include "csvmodel.h"
#include "info.h"
#include "delegate.h"
#include "dialogaboutteams.h"

#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CsvModel *_csvModel;
    About *_windowAbout;
    DialogAboutTeams *_windowAboutTeams;
    QSortFilterProxyModel *_proxyModel;
    Delegate *_delegator;

private slots:
    void loadFile();
    void saveFile();
    void showAbout();
    void addNewRow();
    void removeRows();
    void showDetails();
    void fillTeams();
};

#endif // MAINWINDOW_H

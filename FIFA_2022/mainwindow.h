#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "about.h"
#include "csvmodel.h"
#include "info.h"

#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QMainWindow>
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
    csvModel *_csvModel;
    About *windowAbout;
    QSortFilterProxyModel *proxyModel;

private slots:
    void loadFile();
    void saveFile();
    void showAbout();
    void addNewRow();
    void removeRow();
    void showDetails();
};

#endif // MAINWINDOW_H

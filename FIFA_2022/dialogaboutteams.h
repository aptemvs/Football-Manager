#ifndef DIALOGABOUTTEAMS_H
#define DIALOGABOUTTEAMS_H

#include <QDialog>

namespace Ui {
class DialogAboutTeams;
}

class DialogAboutTeams : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAboutTeams(QWidget *parent = nullptr);
    ~DialogAboutTeams();

private:
    Ui::DialogAboutTeams *ui;
};

#endif // DIALOGABOUTTEAMS_H

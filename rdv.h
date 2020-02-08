#ifndef RDV_H
#define RDV_H

#include <QDialog>

namespace Ui {
class rdv;
}

class rdv : public QDialog
{
    Q_OBJECT

public:
    explicit rdv(QWidget *parent = 0);
    ~rdv();
    QString d;
    QString id_index;


private slots:
    void on_calendarWidget_activated(const QDate &date);

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::rdv *ui;
};

#endif // RDV_H

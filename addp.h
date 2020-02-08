#ifndef ADDP_H
#define ADDP_H

#include <QDialog>
#include<QtSql>

namespace Ui {
class addp;
}

class addp : public QDialog
{
    Q_OBJECT

public:
    explicit addp(QWidget *parent = 0);
    ~addp();
    QSqlDatabase mydb;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::addp *ui;
};

#endif // ADDP_H

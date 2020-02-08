#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QDialog>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>

namespace Ui {
class principal;
}

class principal : public QDialog
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = 0);
    ~principal();

private slots:
    void on_pushButton_a_clicked();

    void on_pushButton_c_clicked();

    void on_pushButton_b_clicked();

    void on_pushButton_d_clicked();

    void on_pushButton_e_clicked();

    void on_pushButton_f_clicked();

    void on_pushButton_clicked();

    void on_pushButton_g_clicked();

private:
    Ui::principal *ui;
};

#endif // PRINCIPAL_H

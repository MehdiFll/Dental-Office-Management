#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include"principal.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    QSqlDatabase mydb;


private slots:
    void on_pushButton_conn_clicked();

private:
    Ui::login *ui;

};

#endif // LOGIN_H

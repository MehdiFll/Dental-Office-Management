#ifndef ADDRDV_H
#define ADDRDV_H

#include <QDialog>

namespace Ui {
class addrdv;
}

class addrdv : public QDialog
{
    Q_OBJECT

public:
    explicit addrdv(QWidget *parent = 0);
    ~addrdv();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::addrdv *ui;
};

#endif // ADDRDV_H

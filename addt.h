#ifndef ADDT_H
#define ADDT_H

#include <QDialog>

namespace Ui {
class addt;
}

class addt : public QDialog
{
    Q_OBJECT

public:
    explicit addt(QWidget *parent = 0);
    ~addt();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::addt *ui;
};

#endif // ADDT_H

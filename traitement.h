#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QDialog>

namespace Ui {
class traitement;
}

class traitement : public QDialog
{
    Q_OBJECT

public:
    explicit traitement(QWidget *parent = 0);
    ~traitement();
    QString id_index;

private slots:
    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::traitement *ui;
};

#endif // TRAITEMENT_H

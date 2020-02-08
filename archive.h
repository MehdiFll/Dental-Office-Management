#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QDialog>

namespace Ui {
class Archive;
}

class Archive : public QDialog
{
    Q_OBJECT

public:
    explicit Archive(QWidget *parent = 0);
    ~Archive();
    QString id_index;

private slots:
    void on_pushButton_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::Archive *ui;
};

#endif // ARCHIVE_H

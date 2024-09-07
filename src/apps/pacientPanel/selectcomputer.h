#ifndef SELECTCOMPUTER_H
#define SELECTCOMPUTER_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidgetItem>

#include "dbworker.h"
#include "picturedialog.h"

namespace Ui {
class SelectComputer;
}

class SelectComputer : public QDialog
{
    Q_OBJECT

public:
    explicit SelectComputer(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~SelectComputer();

public:
    bool setComponentData(const QString& componentName, QComboBox* comboBox);
    bool setDescriptionData(const QString& componentName, QLineEdit* lineEdit);

private slots:
    void on_comboBox_ram_currentTextChanged(const QString &arg1);

    void on_comboBox_gpu_currentTextChanged(const QString &arg1);

    void on_comboBox_cpu_currentTextChanged(const QString &arg1);

    void on_comboBox_storage_currentTextChanged(const QString &arg1);

    void on_comboBox_blockPower_currentTextChanged(const QString &arg1);

    void on_button_selectComputer_clicked();

    void on_listWidget_computers_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::SelectComputer *ui;
    Dbworker *dbworker;
    PictureDialog *pictureDialog;
};

#endif // SELECTCOMPUTER_H

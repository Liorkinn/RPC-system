#ifndef ADDCONFIGURATION_H
#define ADDCONFIGURATION_H

#include <QDialog>
#include <QMessageBox>
#include <QComboBox>
#include "dbworker.h"

namespace Ui {
class AddConfiguration;
}

class AddConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit AddConfiguration(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~AddConfiguration();

public:
    bool setComponentData(const QString& componentName, QComboBox* comboBox);
    bool addConfigurationComputer();
private slots:
    void on_button_configure_clicked();

    void on_button_deleteConfiguration_clicked();

private:
    Ui::AddConfiguration *ui;
    Dbworker *dbworker;
};

#endif // ADDCONFIGURATION_H

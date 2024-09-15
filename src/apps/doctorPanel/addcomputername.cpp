#include "addcomputername.h"
#include "ui_addcomputername.h"

AddComputerName::AddComputerName(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComputerName)
{
    ui->setupUi(this);
    dbworker = p_dbworker;
}

AddComputerName::~AddComputerName()
{
    delete ui;
}

void AddComputerName::addComputer()
{
    QString computerName = ui->lineEdit_computerName->text();
    QString description = ui->lineEdit_description->text();
    QString imagePath = ui->lineEdit_imagePath->text();

    if (computerName.isEmpty() || description.isEmpty() || imagePath.isEmpty()) {
        return;
    }

    bool isAddable = dbworker->addComputerName(computerName, description, imagePath);

    if (isAddable) {
        QMessageBox::information(0, "Добавление ПК", "ПК успешно добавлен!");
        return;
    }
    QMessageBox::critical(0, "Добавление ПК", "Ошибка добавления ПК!");
}

void AddComputerName::on_button_addComputerName_clicked()
{
    addComputer();
}

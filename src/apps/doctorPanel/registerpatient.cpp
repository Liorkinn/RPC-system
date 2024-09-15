#include "registerpatient.h"
#include "ui_registerpatient.h"

RegisterPatient::RegisterPatient(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPatient)
{
    ui->setupUi(this);
    dbworker = p_dbworker;
    this->setFixedSize(249, 276);
}

RegisterPatient::~RegisterPatient()
{
    delete ui;
}

void RegisterPatient::on_button_registratePatient_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString surname = ui->lineEdit_surname->text();
    QString patronymic = ui->lineEdit_patronymic->text();
    int age = ui->lineEdit_age->text().toInt();
    QString telephone = ui->lineEdit_telephone->text();
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if (name.isEmpty() || surname.isEmpty() || patronymic.isEmpty()
            || age == 0 || telephone.isEmpty()
            || login.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(0, "Регистрация", "Пожалуйста, заполните все поля");
        return;
    }

    bool success = dbworker->registerPatient(name, surname, patronymic, age, telephone, login, password);

    if (success) {
        QMessageBox::information(0, "Регистрация", "Владелец успешно зарегистрирован");
    } else {
        QMessageBox::warning(0, "Регистрация", "Владелец не зарегистрирован");
    }
}

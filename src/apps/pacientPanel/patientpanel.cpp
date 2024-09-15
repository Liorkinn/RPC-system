#include "patientpanel.h"
#include "ui_patientpanel.h"

#include "dbworker.h"


PatientPanel::PatientPanel(Dbworker *dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientPanel),
    dbworker(dbworker)
{
    ui->setupUi(this);
    this->setFixedSize(439, 240);
}

PatientPanel::~PatientPanel()
{
    delete ui;
}

void PatientPanel::setUserData(const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone)
{
    QString name = p_name;
    QString surname = p_surname;
    QString patronymic = p_patronymic;
    QString age = p_age;
    QString telephone = p_telephone;

    QString textInitialUser = QString("%1 %2 %3").arg(name).arg(surname).arg(patronymic);
    QString textAge = QString("%1 %2").arg("Возраст: ").arg(age);
    QString textTelephone = QString("%1 %2").arg("Телефон: ").arg(telephone);

    if (textInitialUser.isEmpty() || textAge.isEmpty() || textTelephone.isEmpty()) {
        return;
    }

    setUserID(p_userID);
    setName(p_name);
    setSurname(p_surname);
    setPatronymic(p_patronymic);
    setAge(p_age);
    setTelephone(p_telephone);

    ui->label_FIO->setText(textInitialUser);
    ui->label_age->setText(textAge);
    ui->label_telephone->setText(textTelephone);
}


void PatientPanel::on_button_changePassword_clicked()
{
    changePwd = new changePassword(getUserID(), dbworker);
    changePwd->setWindowTitle("Изменение пароля");
    changePwd->show();
}

void PatientPanel::on_button_selectComputer_clicked()
{
    selectComputer = new SelectComputer(dbworker);
    selectComputer->setWindowTitle("Выбор компьютера");
    selectComputer->show();
}

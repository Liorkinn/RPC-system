#ifndef DBWORKER_H
#define DBWORKER_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

class MainWindow;
class PatientPanel;
class DoctorPanel;

typedef enum {
    USER = 1,
    ADMIN = 2
} roleStatus;


class Dbworker
{
public:
    Dbworker();

/*  Функции
 * - databaseConnection - устанавливает соединение с БД.
 * - authenticateUser - авторизация пользователя.
 * - loadUserInfo - загрузка пользовательских данных.
 * - loadPatientAnimals - загрузка данных о животных.
 * - changeUserPassword - изменение пароля.
 * - checkUserPassword - проверка пароля при изменении пароля.
 * - registerPatient - регистрация пациента.
 * - registerAnimal - регистрация животного.
 * - getPatientData - получение данных о пациенте.
 * - getAnimalTypes - получение типов животных.
 * - bookAppointment - полученение записей на прием.
 * - getAllAnimalsWithOwners - получение животных пользователя.
 * - getAllDoctors - получение всех докторов.
 * - isDoctorBusy - проверка занятости доктора.
 * - getLastDoctorVisitDate - получение последней даты записи.
 * - isDoctorAvailable - проверка наличия доктора.
 * - getDoctorAppointments - получение записей приемов доктора.
 * - addVisitWithDiagnosis - постановка диагноза.
 * - deleteAppointment - отменить запись на приём.
 * - getDoctorVisitDetails - получение данных о визите.
 * - getVisitHistoryForUser - получение истории посещений.
 * - getUserAppointments - получение записей на приём пользователя
*/
public:
    bool databaseConnection                     (const QString &hostname, const int &port, const QString &database, const QString &password = "null");
    bool authenticateUser                       (const QString &login, const QString &password);
    void loadUserInfo                           (int userId, int accessLevelId);
    bool changeUserPassword                     (int userId, const QString &oldPassword, const QString &newPassword);
    bool checkUserPassword                      (int userId, const QString &oldPassword);
    bool registerPatient                        (const QString &name, const QString &surname, const QString &patronymic, int age, const QString &telephone, const QString &login, const QString &password);
    QVariantList getComponents                  (QString component_name);
    QString getDescriptionComponent             (QString component_name);
    QStringList getRecommendedComputers         (QString ram, QString gpu, QString cpu, QString storage, QString block_power);
    QString getPicturePath(QString computer_name);

/*  Функции
 * - m_db - объект для подключения и работы с БД.
 * - patientPanel - объект формы пациента.
 * - doctorPanel - объект формы доктора.
 * - regPanel - объект формы регистратуры.
*/
private:
    QSqlDatabase m_db;
    PatientPanel *patientPanel;
    DoctorPanel *doctorPanel;

};

#endif // DBWORKER_H

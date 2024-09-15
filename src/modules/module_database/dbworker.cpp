#include "dbworker.h"
#include "patientpanel.h"
#include "doctorpanel.h"

Dbworker::Dbworker()
{

}

bool Dbworker::databaseConnection(const QString &hostname, const int &port, const QString &database, const QString &password)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(hostname);
    m_db.setPort(port);
    m_db.setDatabaseName(database);
    m_db.setUserName("postgres");
    m_db.setPassword(password);
    m_db.setConnectOptions("connect_timeout=1");

    if (!m_db.open()) {
        qDebug() << QString("Ошибка подключения к БД: %1").arg(database);
        return false;
    }
    return true;
}

bool Dbworker::authenticateUser(const QString& login, const QString& password) {
    QSqlQuery query(m_db);
    QString command = "SELECT id, access_level_id FROM users WHERE login = :login AND password = :password";

    if (!query.prepare(command)) {
        qDebug() << "Failed to prepare query:" << query.lastError();
        return false;
    }

    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return false;
    }

    int userId = int();
    int accessLevelId = int();

    if (query.next()) {
        userId = query.value(0).toInt();
        accessLevelId = query.value(1).toInt();
        qDebug() << "User authenticated. User ID:" << userId << "Access Level ID:" << accessLevelId;


        if (accessLevelId == USER) {
            patientPanel = new PatientPanel(this);
            patientPanel->setWindowTitle("Пользователь");
            patientPanel->show();
            loadUserInfo(userId, accessLevelId);
        }

        if (accessLevelId == ADMIN) {
            doctorPanel = new DoctorPanel(this);
            doctorPanel->show();
            doctorPanel->setWindowTitle("Администратор");
            loadUserInfo(userId, accessLevelId);
        }
        return true;
    } else {
        qDebug() << "Authentication failed. Invalid login or password.";
        return false;
    }
}

void Dbworker::loadUserInfo(int userId, int accessLevelId)
{
    QSqlQuery query(m_db);
    QString command;
    qDebug() << "ACCESS:" << accessLevelId;

    if (accessLevelId == USER || accessLevelId == ADMIN) {
           command = "SELECT name, surname, patronymic, age, telephone FROM users WHERE id = :userId";
    }


    if (!query.prepare(command)) {
        qDebug() << "Failed to prepare query:" << query.lastError();
        return;
    }

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return;
    }

    if (query.next()) {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString patronymic = query.value(2).toString();
        QString age = query.value(3).toString();
        QString telephone = query.value(4).toString();

        if (accessLevelId == USER) {
            patientPanel->setUserData(userId, name, surname, patronymic, age, telephone);
        } else if (accessLevelId == ADMIN) {
            QString cabinetNumber = query.value(5).toString();
            QString cabinetName = query.value(6).toString();
            QString postType = query.value(7).toString();
            doctorPanel->setUserData(userId, name, surname, patronymic, age, telephone, cabinetNumber, cabinetName, postType);
        }
    }
}

bool Dbworker::changeUserPassword(int userId, const QString& oldPassword, const QString& newPassword) {

    if (!checkUserPassword(userId, oldPassword)) {
        qDebug() << "Incorrect old password.";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("UPDATE public.users SET password = :newPassword WHERE id = :userId");
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to update password:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::checkUserPassword(int userId, const QString& oldPassword) {

    QSqlQuery query(m_db);
    query.prepare("SELECT password FROM public.users WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to fetch user password:" << query.lastError();
        return false;
    }

    QString storedPassword = query.value(0).toString();

    return bool (storedPassword == oldPassword);
}

bool Dbworker::registerPatient(const QString& name, const QString& surname, const QString& patronymic, int age, const QString& telephone, const QString& login, const QString& password) {

    QSqlQuery query(m_db);

    query.prepare("INSERT INTO public.users (name, surname, patronymic, age, telephone, login, password, access_level_id) "
                  "VALUES (:name, :surname, :patronymic, :age, :telephone, :login, :password, 1)");

    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":patronymic", patronymic);
    query.bindValue(":age", age);
    query.bindValue(":telephone", telephone);
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to register patient:" << query.lastError();
        return false;
    }
    return true;
}

QVariantList Dbworker::getComponents(QString component_name)
{
    QSqlQuery query(m_db);
    QVariantList resultList;
    QString componentName = component_name;

    QString command = QString("SELECT CO.option_name, CO.option_description "
                       " FROM Component_Options CO "
                       " JOIN Components C ON CO.component_id = C.id "
                       " WHERE C.name = '%1';").arg(componentName);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
    } else {
        while (query.next()) {
            QVariantMap result;
            result["option_name"] = query.value(0);
            result["option_description"] = query.value(1);
            resultList.append(result);
        }
    }
    return resultList;
}

QString Dbworker::getDescriptionComponent(QString component_name)
{
    QString descriptionComponent = QString();
    QSqlQuery query(m_db);
    QString command = QString("SELECT option_description FROM component_options WHERE option_name = '%1';").arg(component_name);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
    } else {
        while (query.next()) {
            descriptionComponent = query.value(0).toString();
        }
    }
    return descriptionComponent;
}

QStringList Dbworker::getRecommendedComputers(QString ram, QString gpu, QString cpu, QString storage, QString block_power)
{
    QSqlQuery query(m_db);
    QStringList computerNames = QStringList();
    QString command = QString("SELECT DISTINCT c.name AS computer_name "
                              "FROM Computers c "
                              "JOIN Computer_Component_Options cco ON c.id = cco.computer_id "
                              "JOIN Component_Options co ON cco.component_option_id = co.id "
                              "JOIN Components comp ON co.component_id = comp.id "
                              "WHERE (comp.name = 'RAM' AND co.option_name = '%1') "
                                 "OR (comp.name = 'GPU' AND co.option_name = '%2') "
                                 "OR (comp.name = 'CPU' AND co.option_name = '%3') "
                                 "OR (comp.name = 'Storage' AND co.option_name = '%4') "
                                 "OR (comp.name = 'BP' AND co.option_name = '%5') "
                              "GROUP BY c.id "
                              "HAVING COUNT(DISTINCT comp.name) = 5;")
                              .arg(ram)
                              .arg(gpu)
                              .arg(cpu)
                              .arg(storage)
                              .arg(block_power);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return QStringList();
    } else {
        while (query.next()) {
            computerNames.append(query.value(0).toString());
        }
    }
    return computerNames;
}

QString Dbworker::getPicturePath(QString computer_name)
{
    QSqlQuery query(m_db);
    QString pathPicture = QString();

    QString command = QString("SELECT image_path FROM Computers WHERE name = '%1'").arg(computer_name);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return QString();
    } else {
        while (query.next()) {
            pathPicture = query.value(0).toString();
        }
    }
    return pathPicture;
}

QStringList Dbworker::getComponentTypes()
{
    QSqlQuery query(m_db);
    QStringList listTypeComponents = QStringList();

    QString command = QString("SELECT name FROM components;");

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return QStringList();
    } else {
        while (query.next()) {
            listTypeComponents.append(query.value(0).toString());
        }
    }
    return listTypeComponents;
}

bool Dbworker::addComponent(int component_id, QString component_name, QString description)
{
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO public.component_options (component_id, option_name, option_description) "
                  "VALUES (:component_id, :option_name, :option_description)");

    query.bindValue(":component_id", component_id);
    query.bindValue(":option_name", component_name);
    query.bindValue(":option_description", description);

    if (!query.exec()) {
        qDebug() << "Failed to add component:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::addComputerName(QString computer_name, QString description, QString image_path)
{
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO public.computers (name, description, image_path) "
                  "VALUES (:computer_name, :description, :image_path)");

    query.bindValue(":computer_name", computer_name);
    query.bindValue(":description", description);
    query.bindValue(":image_path", image_path);

    if (!query.exec()) {
        qDebug() << "Failed to add computer name:" << query.lastError();
        return false;
    }
    return true;
}

QStringList Dbworker::getComputerName()
{
    QSqlQuery query(m_db);
    QStringList listComputers = QStringList();

    QString command = QString("SELECT name FROM computers;");

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return QStringList();
    } else {
        while (query.next()) {
            listComputers.append(query.value(0).toString());
        }
    }
    return listComputers;
}

bool Dbworker::addConfiguration(int computer_id, int component_option_id)
{
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO public.computer_component_options (computer_id, component_option_id) "
                  "VALUES (:computer_id, :component_option_id)");

    query.bindValue(":computer_id", computer_id);
    query.bindValue(":component_option_id", component_option_id);

    if (!query.exec()) {
        qDebug() << "Failed to add configuration computer:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::deleteComputerComponentOptionsByComputerId(int computer_id)
{
    QSqlQuery query(m_db);

    query.prepare("DELETE FROM Computer_Component_Options WHERE computer_id = :computer_id");
    query.bindValue(":computer_id", computer_id);

    if (!query.exec()) {
        qDebug() << "Failed to delete configuration computer:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::isAvailableComputerConfiguration(QString computer_id)
{
    QSqlQuery query(m_db);
    QStringList id = QStringList();

    QString command = QString("SELECT id FROM computer_component_options WHERE computer_id = '%1';").arg(computer_id);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return bool();
    } else {
        while (query.next()) {
            id.append(query.value(0).toString());
        }
    }

    if (!id.isEmpty()) {
        return false;
    }
    return true;
}

int Dbworker::getComputerId(QString computer_name)
{
    QSqlQuery query(m_db);
    int id = int();

    QString command = QString("SELECT id FROM computers WHERE name = '%1';").arg(computer_name);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return int();
    } else {
        while (query.next()) {
            id = query.value(0).toInt();
        }
    }
    return id;
}

int Dbworker::getComponentId(QString option_name)
{
    QSqlQuery query(m_db);
    int id = int();

    QString command = QString("SELECT id FROM component_options WHERE option_name = '%1';").arg(option_name);

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
        return int();
    } else {
        while (query.next()) {
            id = query.value(0).toInt();
        }
    }
    return id;
}














#include "addconfiguration.h"
#include "ui_addconfiguration.h"

AddConfiguration::AddConfiguration(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConfiguration)
{
    ui->setupUi(this);
    dbworker = p_dbworker;

    setComponentData("CPU", ui->comboBox_cpu);
    setComponentData("RAM", ui->comboBox_ram);
    setComponentData("GPU", ui->comboBox_gpu);
    setComponentData("Storage", ui->comboBox_storage);
    setComponentData("BP", ui->comboBox_blockPower);

    QStringList computerNames = dbworker->getComputerName();

    if (computerNames.isEmpty()) {
        return;
    }

    ui->comboBox_computerName->addItems(computerNames);
}

AddConfiguration::~AddConfiguration()
{
    delete ui;
}

bool AddConfiguration::setComponentData(const QString &componentName, QComboBox *comboBox)
{
    QVariantList componentData = dbworker->getComponents(componentName);

    if (componentData.isEmpty()) {
        return false;
    }

    QStringList listComponent;

    foreach (QVariant componentOption, componentData) {
        QVariantMap componentOptionMap = componentOption.toMap();
        listComponent.append(componentOptionMap["option_name"].toString());
    }

    comboBox->addItems(listComponent);

    return true;
}

bool AddConfiguration::addConfigurationComputer()
{
    QString currentCpu = ui->comboBox_cpu->currentText();
    QString currentRam = ui->comboBox_ram->currentText();
    QString currentGpu = ui->comboBox_gpu->currentText();
    QString currentStorage = ui->comboBox_storage->currentText();
    QString currentBlockPower = ui->comboBox_blockPower->currentText();
    QString currentComputer = ui->comboBox_computerName->currentText();

    int cpuId = dbworker->getComponentId(currentCpu);
    int ramId = dbworker->getComponentId(currentRam);
    int gpuId = dbworker->getComponentId(currentGpu);
    int storageId = dbworker->getComponentId(currentStorage);
    int bpId = dbworker->getComponentId(currentBlockPower);
    int computerId = dbworker->getComputerId(currentComputer);

    bool isAvailable = dbworker->isAvailableComputerConfiguration(QString::number(computerId));
    qDebug() << isAvailable;
    if (!isAvailable) {
        return false;
    }

    dbworker->addConfiguration(computerId, cpuId);
    dbworker->addConfiguration(computerId, ramId);
    dbworker->addConfiguration(computerId, gpuId);
    dbworker->addConfiguration(computerId, storageId);
    dbworker->addConfiguration(computerId, bpId);

    return true;
}


void AddConfiguration::on_button_configure_clicked()
{
    bool isConfiguration = addConfigurationComputer();

    if (!isConfiguration) {
        QMessageBox::critical(0, "Конфигурация", "Компьютер уже сконфигурирован!");
        return;
    }
    QMessageBox::information(0, "Конфигурация", "ПК успешно сконфигурирован!");
}

void AddConfiguration::on_button_deleteConfiguration_clicked()
{
    QString currentComputer = ui->comboBox_computerName->currentText();
    int computerId = dbworker->getComputerId(currentComputer);

    bool isAvailable = dbworker->isAvailableComputerConfiguration(QString::number(computerId));

    qDebug() << isAvailable;

    if (isAvailable) {
        QMessageBox::warning(0, "Удаление конфигурации", "Нет конфигурации для выбранного ПК!");
        return;
    }
    bool isDeleteConfiguration = dbworker->deleteComputerComponentOptionsByComputerId(computerId);

    if (isDeleteConfiguration) {
        QMessageBox::information(0, "Удаление конфигурации", "Конфигурация удалена!");
        return;
    }
    QMessageBox::critical(0, "Удаление конфигурации", "Ошибка удаления конфигурации!");
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    QObject::connect(ui->button_hidePassword, &QPushButton::pressed, [=]() {
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    });

    QObject::connect(ui->button_hidePassword, &QPushButton::released, [=]() {
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    });

    this->setStyleSheet("background-color: pink");
    this->setFixedSize(302, 182);
    dbworker.databaseConnection("127.0.0.1", 5432, "postgres");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_entrance_clicked()
{
    const QString& username = ui->lineEdit_login->text();
    const QString& password = ui->lineEdit_password->text();

    bool isAuthenfication = dbworker.authenticateUser(username, password);

    if (!isAuthenfication) {
        QMessageBox::critical(0, "Авторизация", "Некорректный логин или пароль.");
        return;
    } else {
        hide();
    }
}

#include "registration.h"
#include "ui_registration_window.h"
#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QUrl>

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegistrationWindow), networkManager(new QNetworkAccessManager(this)) {
    ui->setupUi(this);

    connect(ui->sign_up_button, &QPushButton::clicked, this, &RegistrationWindow::on_sign_up_button_clicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &RegistrationWindow::onNetworkReply);
    connect(ui->log_in_button, &QPushButton::clicked, this, &RegistrationWindow::on_log_in_button_clicked);
}

RegistrationWindow::~RegistrationWindow() {
    delete ui;
}

void RegistrationWindow::on_sign_up_button_clicked()
{
    QString username = ui->login_input_field->text();
    QString password = ui->password_input_field->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please fill in all fields");
    } else {
        QJsonObject json;
        json["last_name"] = username;
        json["first_name"] = password;
        json["email"] = "new@example.ru";
        json["role"] = "string";

        QJsonDocument jsonDoc(json);
        QByteArray jsonData = jsonDoc.toJson();

        QUrl url("http://193.19.100.32:7000/api/sign-up");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        networkManager->post(request, jsonData);
    }
}

void RegistrationWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Response:" << response;
        QMessageBox::information(this, "Registration Success", "You have been registered successfully!");
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}

void RegistrationWindow::on_log_in_button_clicked()
{
   emit log_in_button_clicked();
}

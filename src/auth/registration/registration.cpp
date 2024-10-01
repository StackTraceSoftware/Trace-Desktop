#include "auth/registration/registration.h"
#include "./ui_registration_window.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <ui_chats_window.h>
#include <boost/property_tree/ptree.hpp>
#include "utils/custom_windows.h"

#include "chats/chats_window.h"
#include "utils/config_utils.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegistrationWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    [[maybe_unused]] auto log_in_conn = connect(ui->log_in_button, &QPushButton::clicked, this,
                                                &RegistrationWindow::onLogInButtonClicked);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::onSignUpButtonClicked()
{
    try {
        ui->sign_up_button->setText("Loading...");
        const QString username = ui->login_input_field->text();
        const QString password = ui->password_input_field->text();

        if (username.isEmpty() || password.isEmpty()) {
            warning::showCustomWarning(this, "Registration Error", "Please fill in all fields.");
            ui->sign_up_button->setText("Sign Up");
        } else {
            QJsonObject json;
            json["username"] = username;
            json["password"] = password;

            const QJsonDocument jsonDoc(json);
            const QByteArray jsonData = jsonDoc.toJson();

            const QString server_url = config::getServerUrl("config.ini");

            const QUrl url(server_url + "/api/v1/create");
            QNetworkRequest request(url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            if (const QNetworkReply* reply = networkManager->post(request, jsonData); reply->error() == QNetworkReply::NoError) {
                this->hide();
                const auto chat_window = new ChatsWindow();
                chat_window->show();
            } else {
                warning::showCustomWarning(this, "Registration Error", "Something went wrong.");
            }
        }
    } catch (const std::exception &e) {
        warning::showCustomWarning(this, "Registration Error", e.what());
        ui->sign_up_button->setText("Sign Up");
    }
}

void RegistrationWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        const QByteArray response = reply->readAll();
        qDebug() << "Response:" << response;
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}

void RegistrationWindow::onLogInButtonClicked()
{
    emit logInButtonClicked();
}

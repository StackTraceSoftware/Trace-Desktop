#include "auth/registration/registration.h"
#include "./ui_registration_window.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <ui_chats_window.h>
#include <boost/property_tree/ptree.hpp>

#include "chats/chats_window.h"
#include "utils/config_utils.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegistrationWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    [[maybe_unused]] auto log_in_conn = connect(ui->log_in_button, &QPushButton::clicked, this,
                                                &RegistrationWindow::on_log_in_button_clicked);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_sign_up_button_clicked()
{
    try {
        ui->sign_up_button->setText("Loading...");
        const QString username = ui->login_input_field->text();
        const QString password = ui->password_input_field->text();

        if (username.isEmpty() || password.isEmpty()) {
            showCustomWarning(this, "Registration Error", "Please fill in all fields.");
            ui->sign_up_button->setText("Sign Up");
        } else {
            QJsonObject json;
            json["username"] = username;
            json["password"] = password;

            const QJsonDocument jsonDoc(json);
            const QByteArray jsonData = jsonDoc.toJson();

            const QString server_url = config::get_server_url("config.ini");

            const QUrl url(server_url + "/api/v1/create");
            QNetworkRequest request(url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            if (const QNetworkReply* reply = networkManager->post(request, jsonData); reply->error() == QNetworkReply::NoError) {
                this->hide();
                const auto chat_window = new ChatsWindow();
                chat_window->show();
            } else {
                showCustomWarning(this, "Registration Error", "Something went wrong.");
            }
        }
    } catch (const std::exception &e) {
        showCustomWarning(this, "Registration Error", e.what());
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

void RegistrationWindow::on_log_in_button_clicked()
{
    emit log_in_button_clicked();
}

void RegistrationWindow::showCustomWarning(QWidget *parent, const QString &title, const QString &message)
{
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);

    messageBox.setIcon(QMessageBox::Warning);
    config::load_styles(messageBox, "custom_error.qss");

    QPushButton *okButton = messageBox.addButton(QMessageBox::Ok);
    okButton->setFixedSize(70, 40);
    okButton->setCursor(QCursor(Qt::PointingHandCursor));


    messageBox.exec();
}

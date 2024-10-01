#include "./ui_log_in_window.h"
#include "auth/log-in/log_in.h"
#include "utils/custom_windows.h"
#include <./ui_chats_window.h>

#include "chats/chats_window.h"
#include "utils/config_utils.h"

LogInWindow::LogInWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::LogInWindow), networkManager(new QNetworkAccessManager(this)),
      m_stompClient(new StompClient(this))
{
    ui->setupUi(this);
    [[maybe_unused]] auto conn = connect(ui->sign_up_button, &QPushButton::clicked, this,
                                         &LogInWindow::onSignUpButtonClicked);
    connect(this, &LogInWindow::connectWebSocket, m_stompClient, &StompClient::onConnected); // NOLINT(*-unused-return-value)
    connect(ui->log_in_button, &QPushButton::clicked, this, &LogInWindow::onLogInButtonClicked); // NOLINT(*-unused-return-value)
}


LogInWindow::~LogInWindow()
{
    delete ui;
}


void LogInWindow::onSignUpButtonClicked()
{
    emit signUpButtonClicked();
}


void LogInWindow::onLogInButtonClicked()
{
    try
    {
        ui->log_in_button->setText("Loading...");
        const QString username = ui->login_input_field->text();
        const QString password = ui->password_input_field->text();

        if (username.isEmpty() || password.isEmpty())
        {
            warning::showCustomWarning(this, "Error Logged In", "Please fill in all fields");
            ui->log_in_button->setText("Log In");
        }
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;

        const QJsonDocument jsonDoc(json);
        const QByteArray jsonData = jsonDoc.toJson();

        const QString server_url = config::getServerUrl("config.ini");

        const QUrl url(server_url + "/api/v1/auth/login");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    }
    catch (const std::exception& e)
    {
        qDebug() << e.what();
    }
    ok::showCustomOk(this, tr("Logging in"), tr("Logging in"));
    emit connectWebSocket();
    this->close();
    const auto chat_window = new ChatsWindow();
    chat_window->show();
}

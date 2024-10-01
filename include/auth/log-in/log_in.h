#ifndef LOG_IN_H
#define LOG_IN_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include "chats/stomp_client.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class LogInWindow;
}

QT_END_NAMESPACE

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);

    ~LogInWindow() override;

signals:
    void signUpButtonClicked();
    void connectWebSocket();

private slots:
    void onLogInButtonClicked();

    void onSignUpButtonClicked();

private:
    Ui::LogInWindow *ui;
    QNetworkAccessManager *networkManager;
    StompClient *m_stompClient;
};

#endif // LOG_IN_H

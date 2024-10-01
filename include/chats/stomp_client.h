//
// Created by Nick Menshikov on 01.10.2024.
//

#ifndef STOMP_CLIENT_H
#define STOMP_CLIENT_H
#include <QtWebSockets>

class StompClient final : public QObject
{
    Q_OBJECT

public:
    explicit StompClient(QObject* parent = nullptr);
    QString username = "your_username";
    QString nickname = "your_nickname";

public slots:
    void onConnected();

    void sendMessage(const QString& message);

private:
    QWebSocket m_webSocket;
    void sendFrame(const QString& frame);
};
#endif //STOMP_CLIENT_H

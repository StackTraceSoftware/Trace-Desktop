//
// Created by Nick Menshikov on 01.10.2024.
//

#include "chats/stomp_client.h"

StompClient::StompClient(QObject* parent)
{
    m_webSocket.open(QUrl("ws://localhost:8085/ws"));;
}

void StompClient::sendFrame(const QString& frame)
{
    m_webSocket.sendTextMessage(frame);
}

void StompClient::onConnected()
{
    sendFrame(QString("SUBSCRIBE\n"
        "id:sub-0\n"
        "destination:/user/%1/queue/messages\n\n").arg(username));

    sendFrame(QString("SUBSCRIBE\n"
        "id:sub-1\n"
        "destination:/user/public\n\n"));

    QJsonObject json;
    json["username"] = username;
    json["nickname"] = nickname;
    json["status"] = "ONLINE";

    QJsonDocument doc(json);
    QString jsonString(doc.toJson(QJsonDocument::Compact));
    sendFrame(QString("SEND\n"
        "destination:/app/user.addUser\n"
        "cont ent-type:application/json\n"
        "\n%1"
        "\n\n").arg(jsonString));

    qDebug() << "Connected user: " << nickname;
}

void StompClient::sendMessage(const QString& message)
{
    qDebug() << "Message received:" << message;

    const QString subscribeMessage = "SUBSCRIBE\n"
        "id:sub-0\n"
        "destination:/user/your_username/queue/messages\n\n";
    m_webSocket.sendTextMessage(subscribeMessage);

    QJsonObject chatMessage;
    chatMessage["senderId"] = username;
    chatMessage["content"] = message;
    chatMessage["recipientId"] = "your_username1";
    QDateTime currentTime = QDateTime::currentDateTime();
    chatMessage["timestamp"] = currentTime.toString(Qt::ISODate);

    QJsonDocument doc(chatMessage);
    const QString jsonString = doc.toJson(QJsonDocument::Compact);
    qDebug() << "JSON to send:" << jsonString;

    const QString frame = QString("SEND\n"
            "destination:/app/chat\n"
            "content-type:application/json\n"
            "%1\n\n")
        .arg(jsonString);
    sendFrame(frame);
}

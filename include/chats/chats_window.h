#ifndef CHATS_WINDOW_H
#define CHATS_WINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>

#include "stomp_client.h"

namespace Ui
{
    class ChatsWindow;
}

class ChatsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatsWindow(QWidget *parent = nullptr);

    ~ChatsWindow() override;

    Ui::ChatsWindow *ui;

signals:
    void messageToSend(const QString &message) const;

private slots:
    void onChatSelected(QListWidgetItem *item) const;

    void onMessageSend() const;

private:
    void addMessage(const QString &message, bool isUserMessage) const;
    void addChatItem(const QString &chatName, const QString &lastMessage) const;
    StompClient *m_stompClient;

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            emit onMessageSend();
        } else {
            QMainWindow::keyPressEvent(event);
        }
    }
};

#endif // CHATS_WINDOW_H

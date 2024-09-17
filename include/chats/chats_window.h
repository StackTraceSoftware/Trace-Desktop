#ifndef CHATS_WINDOW_H
#define CHATS_WINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class ChatsWindow;
}

class ChatsWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatsWindow(QWidget *parent = nullptr);
    ~ChatsWindow() override;

private slots:
    void on_chat_selected(QListWidgetItem *item) const;
    void on_message_send() const;

private:
    Ui::ChatsWindow *ui;

    void add_message(const QString &message, bool isUserMessage) const;

    static void add_item_with_separator(QListWidget *listWidget, const QString &text);
    void add_chat_item(const QString &chatName, const QString &lastMessage) const;
};

#endif // CHATS_WINDOW_H

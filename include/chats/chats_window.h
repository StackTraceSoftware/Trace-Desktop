#ifndef CHATSWINDOW_H
#define CHATSWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qlistwidget.h>

namespace Ui {
class ChatsWindow;
}

class ChatsWindow : public QMainWindow
{
    Q_OBJECT

public:
    static void addItemWithSeparator(QListWidget *listWidget, const QString &text);

    explicit ChatsWindow(QWidget *parent = nullptr);
    ~ChatsWindow() override;

    void on_chat_selected(const QListWidgetItem *item) const;

    void on_message_send() const;

    void add_message(const QString &message, bool isUserMessage) const;


private:
    Ui::ChatsWindow *ui;
};

#endif // CHATSWINDOW_H

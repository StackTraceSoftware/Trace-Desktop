#ifndef CHAT_CELL_H
#define CHAT_CELL_H

#include <QEvent>
#include <ui_chat_cell.h>

#include "chats_window.h"

namespace Ui
{
    class ChatCell;
}

class ChatCell final : public QWidget
{
    Q_OBJECT

public:
    explicit ChatCell(QWidget *parent = nullptr);

    ~ChatCell() override;

    void setChatName(const QString &name) const;

    void setLastMessage(const QString &message) const;

    [[nodiscard]] QString getChatName() const;

    Ui::ChatCell *ui{};

protected:
    void enterEvent(QEnterEvent *event) override
    {
        this->setStyleSheet("background-color: rgb(56, 56, 69);");
        QWidget::enterEvent(event);
    }

    void leaveEvent(QEvent *event) override
    {
        this->setStyleSheet("background-color: rgb(49, 48, 58);");
        QWidget::leaveEvent(event);
    }
};

#endif // CHAT_CELL_H

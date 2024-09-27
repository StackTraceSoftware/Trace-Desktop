//
// Created by Niсk Menshikov on 14.09.2024.
//

#include "chats/chat_cell.h"

#include <ui_chats_window.h>

#include "./ui_chat_cell.h"

ChatCell::ChatCell(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatCell) {
    ui->setupUi(this);
}

ChatCell::~ChatCell() {
    delete ui;
}

void ChatCell::setChatName(const QString &name) const
{
    ui->chat_name_label->setText(name);
}

void ChatCell::setLastMessage(const QString &message) const
{
    ui->last_message_label->setText(message);
}

QString ChatCell::getChatName() const
{
    return ui->chat_name_label->text();
}

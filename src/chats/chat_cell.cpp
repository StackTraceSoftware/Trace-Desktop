//
// Created by Nik Menshikov on 14.09.2024.
//

#include "chats/chat_cell.h"
#include "./ui_chat_cell.h"
#include <QFrame>

ChatCell::ChatCell(QWidget *parent) :
    QFrame(parent), ui(new Ui::ChatCell) {
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

void ChatCell::set_line_style_sheet(const QString &line_style) const
{
    ui->line->setStyleSheet(line_style);
}

QString ChatCell::getChatName() const
{
    return ui->chat_name_label->text();
}

#include "chats/chats_window.h"


#include "ui_chats_window.h"
#include "chats/chat_cell.h"

ChatsWindow::ChatsWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::ChatsWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 10; ++i) {
        add_chat_item("Chat " + QString::number(i), "Last message from chat " + QString::number(i));
    }

    [[maybe_unused]] auto selected_chat_conn = connect(ui->list_of_chats, &QListWidget::itemClicked, this,
                                                       &ChatsWindow::on_chat_selected);

    [[maybe_unused]] auto message_send_conn = connect(ui->message_input, &QLineEdit::returnPressed, this,
                                                      &ChatsWindow::on_message_send);
}

ChatsWindow::~ChatsWindow()
{
    delete ui;
}

void ChatsWindow::on_chat_selected(QListWidgetItem *item) const
{
    auto const *selected_cell = qobject_cast<ChatCell *>(ui->list_of_chats->itemWidget(item));
    for (int i = 0; i < ui->list_of_chats->count(); ++i) {
        QListWidgetItem *item_of_list = ui->list_of_chats->item(i);
        const auto *cell = qobject_cast<ChatCell *>(ui->list_of_chats->itemWidget(item_of_list));
        if (cell != selected_cell) {
            cell->ui->frame->setStyleSheet(nullptr);
        } else {
            cell->ui->frame->setStyleSheet("background-color: rgb(101, 100, 123);");
        }
    }
    ui->current_chat->clear();
    QWidget *widget = ui->list_of_chats->itemWidget(item);
    const auto *cell = qobject_cast<ChatCell *>(widget);
    const QString selectedChat = cell->getChatName();
    ui->current_chat->addItem("Chat with " + selectedChat);
}

void ChatsWindow::on_message_send() const
{
    if (const QString message = ui->message_input->text(); !message.isEmpty()) {
        add_message("You: " + message, true);
        ui->message_input->clear();
    }
}

void ChatsWindow::add_message(const QString &message, bool isUserMessage) const
{
    auto *item = new QListWidgetItem(message);

    if (isUserMessage) {
        item->setTextAlignment(Qt::AlignRight);
    } else {
        item->setTextAlignment(Qt::AlignLeft);
    }

    ui->current_chat->addItem(item);
}

void ChatsWindow::add_item_with_separator(QListWidget *listWidget, const QString &text)
{
    auto *item = new QListWidgetItem();
    item->setSizeHint(QSize(215, 75));

    auto *widget = new QWidget();
    auto *layout = new QVBoxLayout(widget);
    auto *label = new QLabel(text);
    layout->addWidget(label);

    auto *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: grey;");
    layout->addWidget(separator);
    widget->setLayout(layout);

    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);
}

void ChatsWindow::add_chat_item(const QString &chatName, const QString &lastMessage) const
{
    auto *item = new QListWidgetItem(ui->list_of_chats);
    auto *cell = new ChatCell();
    cell->setChatName(chatName);
    cell->setLastMessage(lastMessage);
    item->setSizeHint(QSize(215, 75));
    ui->list_of_chats->setItemWidget(item, cell);
    ui->list_of_chats->updateGeometry();
}

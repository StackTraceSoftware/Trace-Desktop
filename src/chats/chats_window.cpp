#include "chats/chats_window.h"


#include "ui_chats_window.h"
#include "chats/chat_cell.h"
#include "chats/stomp_client.h"
#include "chats/scroll_bar.h"

ChatsWindow::ChatsWindow(QWidget* parent)
    : QMainWindow(parent)
      , ui(new Ui::ChatsWindow)
      , m_stompClient(new StompClient(this))
{
    ui->setupUi(this);
    auto* scrollBar = new ScrollBar(Qt::Vertical, ui->list_of_chats);
    ui->list_of_chats->setVerticalScrollBar(scrollBar);
    for (int i = 0; i < 20; ++i)
    {
        addChatItem("Chat " + QString::number(i), "Last message from chat " + QString::number(i));
    }
    [[maybe_unused]] auto selected_chat_conn = connect(ui->list_of_chats, &QListWidget::itemClicked, this,
                                                       &ChatsWindow::onChatSelected);

    [[maybe_unused]] auto message_send_conn = connect(ui->message_input, &QLineEdit::returnPressed, this,
                                                      &ChatsWindow::onMessageSend);
    connect(this, &ChatsWindow::messageToSend, m_stompClient, &StompClient::sendMessage);
}

ChatsWindow::~ChatsWindow()
{
    delete ui;
}

void ChatsWindow::onChatSelected(QListWidgetItem* item) const
{
    auto const* selected_cell = qobject_cast<ChatCell*>(ui->list_of_chats->itemWidget(item));
    for (int i = 0; i < ui->list_of_chats->count(); ++i)
    {
        QListWidgetItem* item_of_list = ui->list_of_chats->item(i);
        const auto* cell = qobject_cast<ChatCell*>(ui->list_of_chats->itemWidget(item_of_list));
        if (cell != selected_cell)
        {
            cell->ui->frame->setStyleSheet(nullptr);
        }
        else
        {
            cell->ui->frame->setStyleSheet("background-color: rgb(82, 81, 100);");
        }
    }
    ui->current_chat->clear();
    QWidget* widget = ui->list_of_chats->itemWidget(item);
    const auto* cell = qobject_cast<ChatCell*>(widget);
    const QString selectedChat = cell->getChatName();
    ui->recipientName->setText(selectedChat);
}

void ChatsWindow::onMessageSend() const
{
    if (const QString message = ui->message_input->text(); !message.isEmpty())
    {
        addMessage("You: " + message, true);
        emit messageToSend(message);
        ui->message_input->clear();
    }
}

void ChatsWindow::addMessage(const QString& message, bool isUserMessage) const
{
    auto* item = new QListWidgetItem(message);

    if (isUserMessage)
    {
        item->setTextAlignment(Qt::AlignRight);
    }
    else
    {
        item->setTextAlignment(Qt::AlignLeft);
    }

    ui->current_chat->addItem(item);
}

void ChatsWindow::addChatItem(const QString& chatName, const QString& lastMessage) const
{
    auto* item = new QListWidgetItem(ui->list_of_chats);
    auto* cell = new ChatCell();
    cell->setChatName(chatName);
    cell->setLastMessage(lastMessage);
    item->setSizeHint(QSize(215, 75));
    ui->list_of_chats->setItemWidget(item, cell);
    ui->list_of_chats->updateGeometry();
}

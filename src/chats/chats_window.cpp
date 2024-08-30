#include "chats/chats_window.h"

#include <QtWidgets/QLabel>

#include "ui_chats_window.h"

ChatsWindow::ChatsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatsWindow)
{
    ui->setupUi(this);
    addItemWithSeparator(ui->list_of_chats, "Saved Messages");

    [[maybe_unused]] auto selected_chat_conn = connect(ui->list_of_chats, &QListWidget::itemClicked, this,
                                                       &ChatsWindow::on_chat_selected);

     [[maybe_unused]] auto message_send_conn = connect(ui->message_input, &QLineEdit::returnPressed, this,
                                                       &ChatsWindow::on_message_send);
}

ChatsWindow::~ChatsWindow()
{
    delete ui;
}

void ChatsWindow::on_chat_selected(const QListWidgetItem *item) const
{
    ui->current_chat->clear();

    if (const QString selectedChat = item->text(); selectedChat == "Saved Messages") {
        ui->current_chat->addItem("Welcome to your saved messages!");
    } else {
        ui->current_chat->addItem("Chat with " + selectedChat);
    }
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

void ChatsWindow::addItemWithSeparator(QListWidget *listWidget, const QString &text)
{
    auto *item = new QListWidgetItem();
    item->setSizeHint(QSize(200, 50)); // Размер виджета

    auto *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QLabel *label = new QLabel(text);
    layout->addWidget(label);

    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: grey;");
    layout->addWidget(separator);

    widget->setLayout(layout);

    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);
}

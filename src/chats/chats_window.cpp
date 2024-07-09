#include "chats_window.h"
#include "ui_chats_window.h"

ChatsWindow::ChatsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatsWindow)
{
    ui->setupUi(this);
}

ChatsWindow::~ChatsWindow()
{
    delete ui;
}

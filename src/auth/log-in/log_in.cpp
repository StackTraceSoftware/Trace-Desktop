#include "./ui_log_in_window.h"
#include "auth/log-in/log_in.h"
#include "utils/custom_windows.h"
#include <QMessageBox>
#include <ui_chats_window.h>

#include "chats/chats_window.h"

LogInWindow::LogInWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::LogInWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    [[maybe_unused]] auto conn = connect(ui->sign_up_button, &QPushButton::clicked, this,
                                         &LogInWindow::on_sign_up_button_clicked);
}


LogInWindow::~LogInWindow()
{
    delete ui;
}


void LogInWindow::on_sign_up_button_clicked()
{
    emit sign_up_button_clicked();
}


void LogInWindow::on_log_in_button_clicked()
{
    ok::show_custom_ok(this, tr("Logging in"), tr("Logging in"));
    this->close();
    const auto chat_window = new ChatsWindow();
    chat_window->show();
}

#include "./ui_log_in_window.h"
#include "auth/log-in/log_in.h"

#include <QMessageBox>

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
    QMessageBox::information(this, tr("Logging in"), tr("Logging in"));
}

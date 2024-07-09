#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui
{
class RegistrationWindow;
}
QT_END_NAMESPACE

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

signals:
    void log_in_button_clicked();

private slots:
    void on_sign_up_button_clicked();
    void on_log_in_button_clicked();
    void onNetworkReply(QNetworkReply *reply);

private:
    Ui::RegistrationWindow *ui;
    QNetworkAccessManager *networkManager;
};
#endif

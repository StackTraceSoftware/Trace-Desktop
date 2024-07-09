#ifndef LOG_IN_H
#define LOG_IN_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui
{
class LogInWindow;
}
QT_END_NAMESPACE

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
     explicit LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();

signals:
    void sign_up_button_clicked();

private slots:
    void on_log_in_button_clicked();
    void on_sign_up_button_clicked();

private:
    Ui::LogInWindow *ui;
    QNetworkAccessManager *networkManager;
};

#endif // LOG_IN_H

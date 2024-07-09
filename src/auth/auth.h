#ifndef AUTH_H
#define AUTH_H
#include "QObject"

class LogInWindow;
class RegistrationWindow;

class Auth : public QObject
{
    Q_OBJECT

public:
    Auth();
    void show_registration_window();
    void show_log_in_window();

private:
    LogInWindow *log_in_window;
    RegistrationWindow *registration_window;
};

#endif // AUTH_H

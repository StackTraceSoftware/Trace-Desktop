#include "auth.h"
#include "log-in/log_in.h"
#include "registration/registration.h"

Auth::Auth()
{
    log_in_window = new LogInWindow();
    registration_window = nullptr;
    connect(log_in_window, &LogInWindow::sign_up_button_clicked, this,  &Auth::show_registration_window);
}

void Auth::show_log_in_window()
{
    log_in_window->show();
    if (registration_window) {
        registration_window->hide();
    }
}

void Auth::show_registration_window()
{
    if (!registration_window) {
        registration_window = new RegistrationWindow();
        connect(registration_window, &RegistrationWindow::log_in_button_clicked, this, &Auth::show_log_in_window);
    }
    registration_window->show();
    log_in_window->hide();
}

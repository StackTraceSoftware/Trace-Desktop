#include "auth/auth.h"
#include "auth/log-in/log_in.h"
#include "auth/registration/registration.h"

Auth::Auth()
{
    log_in_window = new LogInWindow();
    registration_window = new RegistrationWindow();
    [[maybe_unused]] auto show_reg_window = connect(log_in_window, &LogInWindow::signUpButtonClicked, this,
                                                    &Auth::show_registration_window);
    [[maybe_unused]] auto show_registration_window = connect(registration_window,
                                                             &RegistrationWindow::logInButtonClicked, this,
                                                             &Auth::show_log_in_window);
}

void Auth::show_log_in_window() const
{
    log_in_window->show();
    registration_window->hide();
}

void Auth::show_registration_window() const
{
    registration_window->show();
    log_in_window->hide();
}

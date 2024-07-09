#include <QApplication>
#include "QtWidgets/qapplication.h"
#include "src/auth/auth.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Auth auth_manager;
    auth_manager.show_log_in_window();
    return a.exec();
}

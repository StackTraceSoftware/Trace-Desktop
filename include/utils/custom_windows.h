//
// Created by Nick Menshikov on 30.08.2024.
//

#ifndef CUSTOM_WINDOWS_H
#define CUSTOM_WINDOWS_H
#include <QtWidgets/QWidget>

namespace warning
{
    void show_custom_warning(QWidget *parent, const QString &title, const QString &message);
}

namespace ok
{
    void show_custom_ok(QWidget *parent, const QString &title, const QString &message);
}
#endif //CUSTOM_WINDOWS_H

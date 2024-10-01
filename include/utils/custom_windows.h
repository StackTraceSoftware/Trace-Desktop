//
// Created by Nick Menshikov on 30.08.2024.
//

#ifndef CUSTOM_WINDOWS_H
#define CUSTOM_WINDOWS_H
#include <QtWidgets/QWidget>

namespace warning
{
    void showCustomWarning(QWidget *parent, const QString &title, const QString &message);
}

namespace ok
{
    void showCustomOk(QWidget *parent, const QString &title, const QString &message);
}
#endif //CUSTOM_WINDOWS_H

//
// Created by Nick Menshikov on 30.08.2024.
//
#include "utils/custom_windows.h"
#include <QtWidgets/QPushButton>
#include "utils/config_utils.h"

void warning::show_custom_warning(QWidget *parent, const QString &title, const QString &message)
{
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);

    messageBox.setIcon(QMessageBox::Warning);
    config::load_styles(messageBox, "custom_error.qss");

    QPushButton *ok_button = messageBox.addButton(QMessageBox::Ok);
    ok_button->setFixedSize(70, 40);
    ok_button->setCursor(QCursor(Qt::PointingHandCursor));


    messageBox.exec();
}

void ok::show_custom_ok(QWidget *parent, const QString &title, const QString &message)
{
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);

    messageBox.setIcon(QMessageBox::Information);
    config::load_styles(messageBox, "custom_error.qss");

    QPushButton *ok_button = messageBox.addButton(QMessageBox::Ok);
    ok_button->setFixedSize(70, 40);
    ok_button->setCursor(QCursor(Qt::PointingHandCursor));


    messageBox.exec();
}


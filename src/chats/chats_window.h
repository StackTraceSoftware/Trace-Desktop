#ifndef CHATSWINDOW_H
#define CHATSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChatsWindow;
}

class ChatsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatsWindow(QWidget *parent = nullptr);
    ~ChatsWindow();

private:
    Ui::ChatsWindow *ui;
};

#endif // CHATSWINDOW_H

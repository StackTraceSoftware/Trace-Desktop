#ifndef CHAT_CELL_H
#define CHAT_CELL_H

#include <QFrame>

namespace Ui {
class ChatCell;
}

class ChatCell : public QFrame {
    Q_OBJECT

public:
    explicit ChatCell(QWidget *parent = nullptr);
    ~ChatCell() override;

    void setChatName(const QString &name) const;
    void setLastMessage(const QString &message) const;
    void set_line_style_sheet(const QString &line_style) const;
    QString getChatName() const;

private:
    Ui::ChatCell *ui{};
};

#endif // CHAT_CELL_H

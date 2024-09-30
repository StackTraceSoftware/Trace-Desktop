//
// Created by Nick Menshikov on 30.09.2024.
//

#ifndef SCROLL_BAR_H
#define SCROLL_BAR_H
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QScrollBar>
#include <QTimer>

class ScrollBar final : public QScrollBar
{
    Q_OBJECT
public:
    explicit ScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);

    void show_scroll_bar_temporarily();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void hide_scroll_bar();

    void sliderChange(SliderChange change) override;

private:
    QTimer *auto_hide_timer;
    QGraphicsOpacityEffect *opacity_effect;
    QPropertyAnimation *fade_animation;
};

#endif //SCROLL_BAR_H

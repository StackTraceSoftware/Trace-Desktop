//
// Created by Nick Menshikov on 30.09.2024.
//
#include "chats/scroll_bar.h"
#include <QPropertyAnimation>

ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget *parent)
{
    setStyleSheet("QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: rgb(49, 48, 58);}");
    auto_hide_timer = new QTimer(this);
    connect(auto_hide_timer, &QTimer::timeout, this, &ScrollBar::hide_scroll_bar);
    auto_hide_timer->setSingleShot(true);

    opacity_effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(opacity_effect);

    fade_animation = new QPropertyAnimation(opacity_effect, "opacity");
    fade_animation->setDuration(500);
    fade_animation->setStartValue(1.0);
    fade_animation->setEndValue(0.0);
}

void ScrollBar::show_scroll_bar_temporarily()
{
    if (auto_hide_timer->isActive()) {
        auto_hide_timer->stop();
    }
    fade_animation->stop();
    opacity_effect->setOpacity(1.0);
    auto_hide_timer->start(2000);
}

void ScrollBar::wheelEvent(QWheelEvent *event)
{
    show_scroll_bar_temporarily();
    QScrollBar::wheelEvent(event);
}

void ScrollBar::hide_scroll_bar()
{
    fade_animation->start();
}

void ScrollBar::sliderChange(const SliderChange change)
{
    show_scroll_bar_temporarily();
    QScrollBar::sliderChange(change);
}

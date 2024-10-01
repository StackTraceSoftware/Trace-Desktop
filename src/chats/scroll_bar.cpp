//
// Created by Nick Menshikov on 30.09.2024.
//
#include "chats/scroll_bar.h"
#include <QPropertyAnimation>

ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget *parent)
{
    setStyleSheet("QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: rgb(49, 48, 58);}");
    autoHideTimer = new QTimer(this);
    connect(autoHideTimer, &QTimer::timeout, this, &ScrollBar::hideScrollBar);
    autoHideTimer->setSingleShot(true);

    opacityEffect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(opacityEffect);

    fadeAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    fadeAnimation->setDuration(500);
    fadeAnimation->setStartValue(1.0);
    fadeAnimation->setEndValue(0.0);
}

void ScrollBar::showScrollBarTemporarily() const
{
    if (autoHideTimer->isActive()) {
        autoHideTimer->stop();
    }
    fadeAnimation->stop();
    opacityEffect->setOpacity(1.0);
    autoHideTimer->start(2000);
}

void ScrollBar::wheelEvent(QWheelEvent *event)
{
    showScrollBarTemporarily();
    QScrollBar::wheelEvent(event);
}

void ScrollBar::hideScrollBar()
{
    fadeAnimation->start();
}

void ScrollBar::sliderChange(const SliderChange change)
{
    showScrollBarTemporarily();
    QScrollBar::sliderChange(change);
}

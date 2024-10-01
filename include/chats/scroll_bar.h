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

    void showScrollBarTemporarily() const;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void hideScrollBar();

    void sliderChange(SliderChange change) override;

private:
    QTimer *autoHideTimer;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *fadeAnimation;
};

#endif //SCROLL_BAR_H

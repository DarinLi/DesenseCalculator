#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScopedPointer>

#include "framelesshelper.h"

class CustomWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

public:
    QVBoxLayout* contentLayout() const;
    QHBoxLayout* titleBarLayout() const;

public:
    void setWindowTitle(const QString &title);
    QString setWindowTitle() const;

    void setWindowIcon(const QPixmap &icon);
    QPixmap icon() const;

    void setTitleBarHeight(const uint height);
    uint titleBarHeight() const;

public:
    FramelessHelper frameLessWidget;//adjust FrameLess Widget

private:
    class CustomWidgetPrivate;
    const QScopedPointer<CustomWidgetPrivate> d;
};

#endif // CUSTOMWIDGET_H

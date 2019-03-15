SOURCES += $$PWD/mainwidget.cpp \
    $$PWD/mainwidgetui.cpp

HEADERS += $$PWD/mainwidget.h \
    $$PWD/mainwidgetui.h

win32 {
QT += winextras
LIBS += -luser32 -ldwmapi
}

INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/mainwidgetui.ui


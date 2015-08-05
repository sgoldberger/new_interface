TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface

QT += gui
QT += widgets
QT += core

SOURCES += \
    mainwindow.cpp \
    waitwindow.cpp \
    targetwindow.cpp \
    actionwindow.cpp \
    connectwindow.cpp \
    main.cpp

HEADERS += \
    mainwindow.h \
    waitwindow.h \
    targetwindow.h \
    actionwindow.h \
    connectwindow.h

symbian: LIBS += -ligtlutil
else:unix|win32: LIBS += -L$$PWD/../OpenIGTLink-build/bin/ -ligtlutil

INCLUDEPATH += $$PWD/../OpenIGTLink/Source
DEPENDPATH += $$PWD/../OpenIGTLink/Source

win32: PRE_TARGETDEPS += $$PWD/../OpenIGTLink-build/bin/igtlutil.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../OpenIGTLink-build/bin/libigtlutil.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenIGTLink-build/bin/release/ -lOpenIGTLink
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenIGTLink-build/bin/debug/ -lOpenIGTLink
else:symbian: LIBS += -lOpenIGTLink
else:unix: LIBS += -L$$PWD/../OpenIGTLink-build/bin/ -lOpenIGTLink

INCLUDEPATH += $$PWD/../OpenIGTLink/Source
DEPENDPATH += $$PWD/../OpenIGTLink/Source

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../OpenIGTLink-build/bin/release/OpenIGTLink.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../OpenIGTLink-build/bin/debug/OpenIGTLink.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../OpenIGTLink-build/bin/libOpenIGTLink.a

INCLUDEPATH += $$PWD/../OpenIGTLink-build
DEPENDPATH += $$PWD/../OpenIGTLink-build

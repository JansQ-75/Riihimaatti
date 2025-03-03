QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balance.cpp \
    creditordebit.cpp \
    environment.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    otheramountwithdrawal.cpp \
    statuswithdrawal.cpp \
    transactions.cpp \
    withdrawal.cpp

HEADERS += \
    balance.h \
    creditordebit.h \
    environment.h \
    login.h \
    mainwindow.h \
    otheramountwithdrawal.h \
    statuswithdrawal.h \
    transactions.h \
    withdrawal.h

FORMS += \
    balance.ui \
    creditordebit.ui \
    login.ui \
    mainwindow.ui \
    otheramountwithdrawal.ui \
    statuswithdrawal.ui \
    transactions.ui \
    withdrawal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    style.qss

RESOURCES += \
    background.qrc \
    riihimaattilogopng.qrc
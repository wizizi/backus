QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addconnwindow.cpp \
    addrulewindow.cpp \
    addstatewindow.cpp \
    adjmatrix.cpp \
    automaton.cpp \
    automatonfield.cpp \
    automatonvertex.cpp \
    changerulewindow.cpp \
    changestatewindow.cpp \
    constructors.cpp \
    grammar.cpp \
    main.cpp \
    mainwindow.cpp \
    regexeqsys.cpp \
    rule.cpp \
    sessiondatagateway.cpp \
    state.cpp \
    tabwidget.cpp \
    taskeditorwindow.cpp \
    taskform.cpp \
    transformations.cpp

HEADERS += \
    addconnwindow.h \
    addrulewindow.h \
    addstatewindow.h \
    adjmatrix.h \
    automaton.h \
    automatonfield.h \
    automatonvertex.h \
    changerulewindow.h \
    changestatewindow.h \
    constructors.h \
    grammar.h \
    mainwindow.h \
    regexeqsys.h \
    rule.h \
    sessiondatagateway.h \
    state.h \
    tabwidget.h \
    taskeditorwindow.h \
    taskform.h \
    transformations.h

FORMS += \
    addconnwindow.ui \
    addrulewindow.ui \
    addstatewindow.ui \
    automatonfield.ui \
    automatonvertex.ui \
    changerulewindow.ui \
    changestatewindow.ui \
    mainwindow.ui \
    tabwidget.ui \
    taskeditorwindow.ui \
    taskform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

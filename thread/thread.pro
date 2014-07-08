TEMPLATE = app
CONFIG += console

INCLUDEPATH += /usr/include \

LIBS += -L/usr/lib/ \
            -lboost_thread-mt -lboost_system-mt

SOURCES += main.cpp



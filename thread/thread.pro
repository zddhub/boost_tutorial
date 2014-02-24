TEMPLATE = app
CONFIG += console

INCLUDEPATH += /home/zdd/boost_1_55_0 \

LIBS += -L/home/zdd/boost_1_55_0/stage/lib/ \
            -lboost_thread -lboost_system

SOURCES += main.cpp



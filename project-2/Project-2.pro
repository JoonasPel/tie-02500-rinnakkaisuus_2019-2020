TEMPLATE = app

CONFIG += cmdline c++14

CONFIG -= qt
QT -= core gui concurrent

LIBS += -pthread

# Use course library
include( concur2020lib/concur2020.pri )

# Implement your code here:
SOURCES += \
    main.cpp

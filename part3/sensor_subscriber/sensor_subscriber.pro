QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# Specify path to RTI installation
RTIDDS_PREFIX = $$(NDDSHOME)
RTIDDS_VERSION = x64Linux3gcc5.4.0

RTIDDS_IDL = ../common/sensor.idl

include(../common/dds.pri)

SOURCES += \
        main.cpp

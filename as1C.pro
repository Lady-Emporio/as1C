#-------------------------------------------------
#
# Project created by QtCreator 2018-09-01T08:34:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = as1C
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Settings/settings.cpp \
    Settings/settings_gui.cpp \
    BaseObject/basetable.cpp \
    Documents/Orderslist/orders_list.cpp \
    mw_opens/orders_open.cpp \
    Documents/Order/order.cpp \
    BaseObject/basechoose.cpp \
    BaseObject/subtable.cpp \
    Documents/Phone/phoneslist.cpp \
    Documents/Phone/phone.cpp \
    mw_opens/phones_open.cpp \
    BaseObject/delegate.cpp \
    Documents/Call/call.cpp \
    Catalogs/Dealers/dealers.cpp \
    Catalogs/Dealers/dealers_list.cpp \
    mw_opens/dealers_open.cpp \
    BaseObject/neutral_func.cpp

HEADERS  += mainwindow.h \
    Settings/settings.h \
    Settings/settings_gui.h \
    allinclude.h \
    BaseObject/basetable.h \
    Documents/Orderslist/orders_list.h \
    Documents/Order/order.h \
    BaseObject/basechoose.h \
    BaseObject/subtable.h \
    Documents/Phone/phoneslist.h \
    Documents/Phone/phone.h \
    BaseObject/delegate.h \
    Documents/Call/call.h \
    Catalogs/Dealers/dealers.h \
    Catalogs/Dealers/dealers_list.h \
    BaseObject/neutral_func.h

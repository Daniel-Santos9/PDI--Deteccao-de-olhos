#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T15:56:29
#
#-------------------------------------------------

QT       += core

QT       += gui

TARGET = PROJETO
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    funcoes.cpp \
    histograma.cpp \
    limiarizacao.cpp \
    meth_otsu.cpp \
    coletaPontos.cpp \
    layer.cpp \
    mlp.cpp \
    neuron.cpp \
    treina.cpp \
    dendrite.cpp \
    gravaDados.cpp \
    testa.cpp

INCLUDEPATH += "C:\OpenCV-QT\install\include"
LIBS += -L"C:\OpenCV-QT\install\x86\mingw\bin" \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_videoio320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320

HEADERS += \
    funcoes.h \
    histograma.h \
    limiarizacao.h \
    meth_otsu.h \
    coletaPontos.h \
    layer.h \
    mlp.h \
    neuron.h \
    treina.h \
    dendrite.h \
    gravaDados.h \
    testa.h

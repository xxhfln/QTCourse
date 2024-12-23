QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    licenseplaterecognition.cpp \
    opencvtool.cpp \
    recognition.cpp

HEADERS += \
    common.h \
    licenseplaterecognition.h \
    opencvtool.h \
    recognition.h

FORMS += \
    licenseplaterecognition.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 配置opencv
INCLUDEPATH += D:\OpenCV\opencv\build_opencv\install\include
LIBS += D:\OpenCV\opencv\build_opencv\install\x64\mingw\bin\libopencv_*.dll

RESOURCES += \
    res.qrc

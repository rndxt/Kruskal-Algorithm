QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a no_keywords warn_on

win32 {
  win32-msvc*{
    QMAKE_CXXFLAGS_WARN_ON ~= s/-W./-W4
    QMAKE_CXXFLAGS += /MP /permissive-

    LIBS += -luser32
  }

  win32-g++*{

  }

  win32-clang*{

  }
}

linux {
  linux-g++*{
  }

  linux-clang*{
  }
}

macx {
  macx-g++*{
  }

 macx-clang*{
 }
}

include($${OUT_PWD}/conanbuildinfo.pri)

# Qwt
DEFINES += $$CONAN_DEFINES_QWT
INCLUDEPATH += $$CONAN_INCLUDEPATH_QWT
LIBS += $$CONAN_LIBDIRS_QWT $$CONAN_LIBS_QWT

SOURCES += \
  Interface/MainWindow.cpp \
  Kernel/AlgorithmAnimator.cpp \
  Kernel/AlgorithmController.cpp \
  Kernel/AlgorithmModel.cpp \
  Kernel/NodeAnimator.cpp \
  Interface/PlotController.cpp \
  Interface/View.cpp \
  Kernel/Graph.cpp \
  Kernel/DisjointSet.cpp \
  Kernel/Algorithm.cpp \
  Kernel/GeomModel.cpp \
  Kernel/Palette.cpp \
  Library/QTimeAnchor.cpp \
  Library/Random.cpp \
  Library/Time.cpp \
  Application.cpp \
  ApplicationGUI.cpp \
  ApplicationKernel.cpp \
  ApplicationImpl.cpp \
  Except.cpp \
  QPorts.cpp \
  QRunTime.cpp \
  main.cpp \


HEADERS += \
  Interface/MainWindow.h \
  Kernel/AlgorithmAction.h \
  Kernel/AlgorithmAnimator.h \
  Kernel/AlgorithmController.h \
  Kernel/AlgorithmModel.h \
  Kernel/EdgeStatus.h \
  Kernel/NodeAnimator.h \
  Interface/PlotController.h \
  Interface/View.h \
  Kernel/DrawData.h \
  Kernel/Graph.h \
  Kernel/DisjointSet.h \
  Kernel/Algorithm.h \
  Kernel/GeomModel.h \
  Kernel/MouseAction.h \
  Kernel/NodeStatus.h \
  Kernel/Palette.h \
  Library/QTimeAnchor.h \
  Library/Random.h \
  Library/Time.h \
  Application.h \
  ApplicationGUI.h \
  ApplicationKernel.h \
  ApplicationImpl.h \
  Except.h \
  QObserver.h \
  QPorts.h \
  QRunTime.h


FORMS += \
    Interface/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

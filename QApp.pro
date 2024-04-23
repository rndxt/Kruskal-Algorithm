QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a no_keywords warn_on

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

#INCLUDEPATH += modules


# This code chooses the conanfile and then run conan on it.
# If you use this, you do not need to specify the conan install step.
# But you have to run the qmake twice!

# This copies the conan file of choice.
#QMAKE_EXTRA_TARGETS += copy_conanfile
#CONAN_FILE_PATH = $$PWD/conan
#CONAN_FILE_PATH = $$CONAN_FILE_PATH/static
#copy_conanfile.target = conanfile
#copy_conanfile.commands = $(COPY_FILE) \
#                          $$shell_path($$CONAN_FILE_PATH/conanfile.txt) \
#                          $$shell_path($$PWD)
#PRE_TARGETDEPS += conanfile


#CONFIG(debug, debug|release) {
#    CONAN_BUILD_TYPE = Debug
#} else {
#    CONAN_BUILD_TYPE = Release
#}
#QMAKE_EXTRA_TARGETS += conan_install
#conan_install.target = conan_install
#conan_install.commands = conan install "-if $$OUT_PWD" "-s build_type=$$CONAN_BUILD_TYPE" "--build=missing" $$PWD/conanfile.txt
#PRE_TARGETDEPS += conan_install


#CONFIG += conan_basic_setup
include($${OUT_PWD}/conanbuildinfo.pri)

# Qwt
DEFINES += $$CONAN_DEFINES_QWT
INCLUDEPATH += $$CONAN_INCLUDEPATH_QWT
LIBS += $$CONAN_LIBDIRS_QWT $$CONAN_LIBS_QWT
#LIBS += -L$$CONAN_BINDIRS_QWT

# this copies the required files, but it seems like dll is incompatible
# should find out how to set the correct build settings of qwt with conan
#QMAKE_EXTRA_TARGETS += qwt_copy_dll
#qwt_copy_dll.target = qwt_dll
#qwt_copy_dll.commands = $(COPY_DIR) \
#                          $$shell_path($$CONAN_BINDIRS_QWT) \
#                          $$shell_path($$OUT_PWD)
#QMAKE_POST_LINK += $${qwt_copy_dll.commands}

##OneApi TBB
#DEFINES += $$CONAN_DEFINES_ONETBB
#INCLUDEPATH += $$CONAN_INCLUDEPATH_ONETBB
#LIBS += $$CONAN_LIBDIRS_ONETBB $$CONAN_LIBS_ONETBB
## this path contains required dlls and is added to the run environment by QtCreator
## make sure to check Run option "Add build library search path to Path"
##LIBS += -L$$CONAN_BINDIRS_ONETBB

# this copies onetbb dlls to the target executable directory
#CONFIG(debug, debug|release) {
#    BUILD_TYPE = debug
#} else {
#    BUILD_TYPE = release
#}
#QMAKE_EXTRA_TARGETS += onetbb_copy_dll
#onetbb_copy_dll.target = onetbb_dll
#onetbb_copy_dll.commands = $(COPY_DIR) \
#                          $$shell_path($$CONAN_BINDIRS_ONETBB) \
#                          $$shell_path($$OUT_PWD/$$BUILD_TYPE)
#QMAKE_POST_LINK += $${onetbb_copy_dll.commands}

SOURCES += \
  Interface/MainWindow.cpp \
    Kernel/AlgorithmController.cpp \
    Kernel/AlgorithmModel.cpp \
  dialog.cpp \
  Interface/PlotController.cpp \
  Interface/View.cpp \
  Kernel/Graph.cpp \
  Kernel/DisjointSet.cpp \
  Kernel/Algorithm.cpp \
  Kernel/GeomModel.cpp \
  Kernel/Palette.cpp \
  Kernel/ItemAnimator.cpp \
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
  Kernel/AlgorithmController.h \
  Kernel/AlgorithmModel.h \
  dialog.h \
  Interface/PlotController.h \
  Interface/View.h \
  Kernel/DrawData.h \
  Kernel/Graph.h \
  Kernel/DisjointSet.h \
  Kernel/Algorithm.h \
  Kernel/GeomModel.h \
  Kernel/MouseAction.h \
  Kernel/Palette.h \
  Kernel/ItemAnimator.h \
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

#-------------------------------------------------
#
# Project created by QtCreator 2019-02-04T17:55:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OscTester
TEMPLATE = app

include(QOSC/QOSC.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        osctester.cpp \
    inputconverter.cpp \
    verticalscrollarea.cpp \
    sendcontainer.cpp \
    oscreceiver.cpp \
    receivertabarea.cpp \
    aboutosctesterapp.cpp

HEADERS += \
        osctester.h \
    inputconverter.h \
    verticalscrollarea.h \
    sendcontainer.h \
    oscreceiver.h \
    receivertabarea.h \
    aboutosctesterapp.h

FORMS += \
    oscreceiver.ui \
    osctester.ui \
    aboutosctesterapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: ICON = oscTesterIcon.icns

DISTFILES +=

RESOURCES += \
    osctester.qrc

GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)

QMAKE_TARGET_PRODUCT = "Osc Tester"
QMAKE_TARGET_COMPANY = "TeamLab"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) by TeamLab"

DEFINES += APP_VERSION=\"\\\"$${GIT_VERSION}\\\"\" \
#DEFINES += APP_VERSION=\"\\\"$${APP_VERSION}\\\"\" \
           GIT_PRODUCT=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\" \
           APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\" \
           APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"

#macx {
#    INFO_PLIST_PATH = $$shell_quote($${OUT_PWD}/$${TARGET}.app/Contents/Info.plist)
##    QMAKE_POST_LINK += /usr/libexec/PlistBuddy -c \"Set :CFBundleShortVersionString $${GIT_VERSION}\" $${INFO_PLIST_PATH}
#    plistupdate.commands = /usr/libexec/PlistBuddy -c \"Set :CFBundleShortVersionString $$VERSION\", \"Set :CFBundleVersionString $$VERSION\" $$QMAKE_INFO_PLIST
#}

macx{
    QTPROJECTS = /Users/kozakiyuta/Qt/apps
    PLISTLOC = $${QTPROJECTS}/plist
    PROPKGLOC = $${QTPROJECTS}/pkgpath
    PRORESLOC = $${QTPROJECTS}/resource

    QMAKE_EXTRA_TARGETS += codesign product
    codesign.commands += $${QTPATH}/bin/macdeployqt $${TARGET}.app -verbose=3;
    codesign.commands += cp $${PLISTLOC}/Infoplist/Info.plist $${TARGET}.app/Contents/Info.plist;
    product.commands += productbuild --component $${TARGET}.app /Applications --sign \"$${INSTALLERCERT}\" $${TARGET}.pkg;
}


#QMAKE_INFO_PLIST +=  $${TARGET}/data/default.plist
#QMAKE_INFO_PLIST +=  $${TARGET}/Contents/info.plist
#QMAKE_POST_LINK += sed -i -e "s/@VERSION@/$$VERSION/g" "./$${TARGET}.app/Contents/Info.plist";
#QMAKE_POST_LINK += sed -i -e "s/@VERSION@/$$APP_VERSION/g" "./$${TARGET}.app/Contents/Info.plist";

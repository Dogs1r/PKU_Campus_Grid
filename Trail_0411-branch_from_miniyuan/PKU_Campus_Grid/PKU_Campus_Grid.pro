QT       += core gui
QT       += svgwidgets
QT       += svg
QT       += core gui xml
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aichatwidget.cpp \
    bookmarkmanager.cpp \
    bookmarkwidget.cpp \
    buildingdetailwidget.cpp \
    buildinginfomanager.cpp \
    buildinginteractionsystem.cpp \
    canteenmanager.cpp \
    dragpanbutton.cpp \
    fancytoolbar.cpp \
    floattingtoolbar.cpp \
    foodfinderwidget.cpp \
    languagemanager.cpp \
    loginwidget.cpp \
    main.cpp \
    maintoolbar.cpp \
    mainwindow.cpp \
    mapinfowidget.cpp \
    mapmenubar.cpp \
    mapnavigatewidget.cpp \
    mapview.cpp \
    momentedit.cpp \
    momentwidget.cpp \
    registerdialog.cpp \
    routefinder.cpp \
    slotmachinedialog.cpp \
    studyfinderwidget.cpp \
    themesettingwidget.cpp \
    translatablestring.cpp

HEADERS += \
    aichatwidget.h \
    bookmarkmanager.h \
    bookmarkwidget.h \
    buildingdetailwidget.h \
    buildinginfomanager.h \
    buildinginteractionsystem.h \
    canteenmanager.h \
    dragpanbutton.h \
    fancytoolbar.h \
    floattingtoolbar.h \
    foodfinderwidget.h \
    languagemanager.h \
    loginwidget.h \
    maintoolbar.h \
    mainwindow.h \
    mapinfowidget.h \
    mapmenubar.h \
    mapnavigatewidget.h \
    mapview.h \
    momentedit.h \
    momentwidget.h \
    registerdialog.h \
    routefinder.h \
    slotmachinedialog.h \
    studyfinderwidget.h \
    themesettingwidget.h \
    translatablestring.h

FORMS += \
    aichatwidget.ui \
    bookmarkmanager.ui \
    bookmarkwidget.ui \
    buildingdetailwidget.ui \
    buildinginfomanager.ui \
    buildinginteractionsystem.ui \
    canteenmanager.ui \
    dragpanbutton.ui \
    fancytoolbar.ui \
    floattingtoolbar.ui \
    foodfinderwidget.ui \
    languagemanager.ui \
    loginwidget.ui \
    maintoolbar.ui \
    mainwindow.ui \
    mapinfowidget.ui \
    mapmenubar.ui \
    mapnavigatewidget.ui \
    momentedit.ui \
    momentwidget.ui \
    registerdialog.ui \
    routefinder.ui \
    slotmachinedialog.ui \
    studyfinderwidget.ui \
    themesettingwidget.ui \
    translatablestring.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

TRANSLATIONS += \
    lang_zh_CN.ts \  # 中文翻译文件
    lang_en_US.ts    # 英文翻译文件

DISTFILES +=

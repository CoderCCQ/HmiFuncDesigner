include(../../DrawApplicationPlugin.pri)
include(../../QtPropertyBrowserEx/QtPropertyBrowserEx.pri)

CONFIG(debug, debug|release) { #debug
    win32 {
        LIBS += -L$$IDE_LIBRARY_PATH -lQtPropertyBrowserd
        LIBS += -L$$LINK_LIBRARY_PATH -lProjectDataUtilsd
        LIBS += -L$$LINK_LIBRARY_PATH -lUtilsd
        LIBS += -L$$LINK_LIBRARY_PATH -lDrawUtilsd
        LIBS += -L$$LINK_LIBRARY_PATH -lqscintilla2_qt$${QT_MAJOR_VERSION}d
    }
    unix {
        LIBS += -L$$IDE_LIBRARY_PATH -lQtPropertyBrowser
        LIBS += -L$$LINK_LIBRARY_PATH -lProjectDataUtils
        LIBS += -L$$LINK_LIBRARY_PATH -lUtils
        LIBS += -L$$LINK_LIBRARY_PATH -lDrawUtils
        LIBS += -L$$LINK_LIBRARY_PATH -lqscintilla2_qt$${QT_MAJOR_VERSION}
    }
} else { # release
    LIBS += -L$$IDE_LIBRARY_PATH -lQtPropertyBrowser
    LIBS += -L$$LINK_LIBRARY_PATH -lProjectDataUtils
    LIBS += -L$$LINK_LIBRARY_PATH -lUtils
    LIBS += -L$$LINK_LIBRARY_PATH -lDrawUtils
    LIBS += -L$$LINK_LIBRARY_PATH -lqscintilla2_qt$${QT_MAJOR_VERSION}
}

SOURCES += \
    ../../Public/Element.cpp \
    ../../Public/PubTool.cpp \
    ElementJarShape.cpp \
    JarShapePlugin.cpp \
    editbasicpropertydialog.cpp

HEADERS += \
    ../../Public/PubTool.h \
    ../../Public/PublicDefine.h \
    ../../Public/PublicDefine.h \
    ../../IDrawApplicationPlugin/IDrawApplicationPlugin.h \
    ../../Public/Element.h \
    ElementJarShape.h \
    JarShapePlugin.h \
    editbasicpropertydialog.h

DISTFILES += EJarShape.json

RESOURCES += \
    images.qrc

FORMS += \
    editbasicpropertydialog.ui



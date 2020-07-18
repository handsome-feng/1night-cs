qmake -query QT_INSTALL_DIR

make install INSTALL_ROOT=/tmp

## i18N:
foo.pro(qmake > 5.14):
TRANSLATIONS += foo_zh_CN.ts
QM_FILES_INSTALL_PATH = /usr/share/foo/translations/
CONFIG += lrelease

# So we can access it from main.cpp
DEFINES += QM_FILES_INSTALL_PATH='\\"$${QM_FILES_INSTALL_PATH}\\"'


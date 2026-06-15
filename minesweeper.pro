TEMPLATE = app
TARGET = minesweeper
CONFIG += console c++17

SOURCES += \
    main.cpp \
    MinesweeperBoard.cpp \
    MSBoardTextView.cpp \
    MSTextController.cpp \
    MSSFMLView.cpp \
    MSSFMLController.cpp

HEADERS += \
    Field.h \
    GameMode.h \
    MinesweeperBoard.h \
    MSBoardTextView.h \
    MSTextController.h \
    MSSFMLView.h \
    MSSFMLController.h

# SFML include and library paths for MSYS2/MinGW
INCLUDEPATH += C:/msys64/ucrt64/include
LIBS += -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system

# If using a different SFML installation path, update INCLUDEPATH and LIBS above.

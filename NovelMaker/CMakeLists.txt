cmake_minimum_required(VERSION 3.16)

project(NovelMaker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CORE
    src/core/main.cpp
    src/core/logger.h src/core/logger.cpp
)

set(WINDOWS
    src/windows/enumlistwidget.h
    src/windows/mainwindow.h src/windows/mainwindow.cpp src/windows/mainwindow.ui
    src/windows/mainwidget.h src/windows/mainwidget.cpp src/windows/mainwidget.ui
    src/windows/settingwidget.h src/windows/settingwidget.cpp src/windows/settingwidget.ui
)

set(SRC
    ${CORE}
    ${WINDOWS}
)

set(PROJECT_SOURCES
    ${SRC}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(NovelMaker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    src/utilitis/configutilities.h src/utilitis/configutilities.cpp
    src/windows/worldwidget.h src/windows/worldwidget.cpp src/windows/worldwidget.ui
    src/windows/characterwidget.h src/windows/characterwidget.cpp src/windows/characterwidget.ui



)

target_include_directories(NovelMaker PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(NovelMaker PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(NovelMaker PRIVATE Qt6::Core)
target_link_libraries(NovelMaker PRIVATE Qt6::Core)
target_link_libraries(NovelMaker PRIVATE Qt6::Core)

set_target_properties(NovelMaker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS NovelMaker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(NovelMaker)

cmake_minimum_required(VERSION 3.16)

project(NovelMaker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(MAIN
    src/main/main.cpp
)

set(UI
    src/ui/enumlistwidget.h
    src/ui/mainwindow.h src/ui/mainwindow.cpp src/ui/mainwindow.ui
    src/ui/mainwidget.h src/ui/mainwidget.cpp src/ui/mainwidget.ui
    src/ui/settingwidget.h src/ui/settingwidget.cpp src/ui/settingwidget.ui
)

set(SRC
    ${MAIN}
    ${UI}
)

set(PROJECT_SOURCES
    ${SRC}
)

set(RES_SRC "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(RES_DST "$<TARGET_FILE_DIR:NovelMaker>/res")

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(NovelMaker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(NovelMaker PRIVATE 
Qt${QT_VERSION_MAJOR}::Widgets
CommonUI
DataManager
)

target_include_directories(NovelMaker PRIVATE ${PROJECT_SOURCE_DIR})

set_target_properties(NovelMaker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_custom_command(TARGET NovelMaker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RES_SRC}
    ${RES_DST}
    COMMENT "正在复制 style 文件夹到运行目录..."
)

include(GNUInstallDirs)
install(TARGETS NovelMaker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(NovelMaker)

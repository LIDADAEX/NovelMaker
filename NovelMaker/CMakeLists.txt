cmake_minimum_required(VERSION 3.16)

project(NovelMaker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SRC_CORE
    src/core/main.cpp
    src/core/logger.h src/core/logger.cpp
)

set(SRC_WINDOWS
    src/windows/enumlistwidget.h
    src/windows/mainwindow.h src/windows/mainwindow.cpp src/windows/mainwindow.ui
    src/windows/mainwidget.h src/windows/mainwidget.cpp src/windows/mainwidget.ui
    src/windows/settingwidget.h src/windows/settingwidget.cpp src/windows/settingwidget.ui
    src/windows/worldwidget.h src/windows/worldwidget.cpp src/windows/worldwidget.ui
    src/windows/characterwidget.h src/windows/characterwidget.cpp src/windows/characterwidget.ui
    src/windows/widgetbase.h src/windows/widgetbase.cpp
)

set(SRC_UTILITIES
    src/utilitis/config/configdefine.h
    src/utilitis/config/configsystem.h src/utilitis/config/configsystem.cpp
    src/utilitis/config/configproject.h src/utilitis/config/configproject.cpp
    src/utilitis/config/configuser.h src/utilitis/config/configuser.cpp
    src/utilitis/config/configworkspace.h src/utilitis/config/configworkspace.cpp
    src/utilitis/config/configmanager.h src/utilitis/config/configmanager.cpp
    src/utilitis/config/configbase.h src/utilitis/config/configbase.cpp
    src/utilitis/file/fileutil.h src/utilitis/file/fileutil.cpp
    src/utilitis/file/jsonfileutil.h src/utilitis/file/jsonfileutil.cpp
    src/utilitis/style/stylemanager.h src/utilitis/style/stylemanager.cpp
    src/utilitis/style/styleutil.h src/utilitis/style/styleutil.cpp
    src/utilitis/style/styledefine.h
)

set(SRC
    ${SRC_CORE}
    ${SRC_WINDOWS}
    ${SRC_UTILITIES}
)

set(RES_STYLE
)

set(RES_CONFIG
)

set(RES
    ${RES_STYLE}
    ${RES_CONFIG}
)

set(PROJECT_SOURCES
    ${SRC}
    ${RES}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(NovelMaker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    widget/textbrowser.h widget/textbrowser.cpp

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

add_custom_command(
    TARGET NovelMaker
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:NovelMaker>/res

    COMMENT "Copying 'res' directory to build folder..."
)

qt_finalize_executable(NovelMaker)

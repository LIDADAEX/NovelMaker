cmake_minimum_required(VERSION 3.16)

project(CommonUI LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(CommonUI SHARED
  CommonUI_global.h
  include/styles/qssmerger.h src/styles/qssmerger.cpp
  src/styles/qsslorder.cpp include/styles/qsslorder.h src/styles/qssmanager.cpp include/styles/qssmanager.h
  src/styles/qssmerger.cpp include/styles/qssmerger.h
)

target_link_libraries(CommonUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CommonUI PRIVATE Qt6::Widgets)
target_include_directories(CommonUI PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(CommonUI PRIVATE COMMONUI_LIBRARY)

cmake_minimum_required(VERSION 3.16)

project(NovelMakerTop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(lib/CommonUI)
add_subdirectory(lib/DataManager)

add_subdirectory(NovelMaker)

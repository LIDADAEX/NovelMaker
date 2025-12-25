cmake_minimum_required(VERSION 3.16)

# 定义整个解决方案的名称
project(NovelMakerTop LANGUAGES CXX)

# 设置一些全局变量，比如 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 Qt 的自动处理 (MOC, UIC, RCC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 核心步骤：添加子目录
# 这会去寻找 MyUtils 文件夹下的 CMakeLists.txt 并执行它
add_subdirectory(lib/CommonUI)
add_subdirectory(lib/DataManager)

# 添加主程序目录
add_subdirectory(NovelMaker)
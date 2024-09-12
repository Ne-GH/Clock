cmake_minimum_required(VERSION 3.29)
project(Clock)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

#[[
add_library(Module)
target_sources(Module
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Time.cppm
)
]]

add_executable(Clock main.cpp
        MainWindow.h
        MainWindow.cpp

        Time.h
        Time.cpp

 )



target_link_libraries(Clock
        Qt::Core
        Qt::Gui
        Qt::Widgets
        # Module
)



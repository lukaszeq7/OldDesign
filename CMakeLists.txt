cmake_minimum_required(VERSION 3.26)
project(OldDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED
)

add_executable(OldDesign main.cpp
        MainWindow.cpp
        MainWindow.h
        BedModel.cpp
        BedModel.h
        Bed.cpp
        Bed.h
        Database.cpp
        Database.h
        Application.cpp
        Application.h
        NewBedWidget.cpp
        NewBedWidget.h
        NewBedWidget.ui
        BedsWidget.cpp
        BedsWidget.h
        BedsWidget.ui
)

target_link_libraries(OldDesign
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
)

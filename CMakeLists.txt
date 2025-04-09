cmake_minimum_required(VERSION 3.16)
project(StereoDisparityApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCES
    main.cpp
    mainwindow.cpp
    imageprocessor.cpp
)

set(HEADERS
    mainwindow.h
    imageprocessor.h
)

set(UIS
    mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets ${OpenCV_LIBS})

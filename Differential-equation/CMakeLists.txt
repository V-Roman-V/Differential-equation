cmake_minimum_required(VERSION 3.5)

project(Differential-equation LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        window/mainwindow.cpp
        window/mainwindow.h
        window/mainwindow.ui
        QCustomPlot/qcustomplot.cpp
        QCustomPlot/qcustomplot.h
        graphics/plot.cpp
        graphics/plot.h
        graphics/function.cpp
        graphics/function.h
        graphics/exactsolution.cpp
        graphics/exactsolution.h
        graphics/eulermethod.cpp
        graphics/eulermethod.h
        graphics/improvedeulermethod.cpp
        graphics/improvedeulermethod.h
        graphics/rungekuttamethod.cpp
        graphics/rungekuttamethod.h
        graphics/approximationmethod.cpp
        graphics/approximationmethod.h
        graphics/parameters.cpp
        graphics/parameters.h
        graphics/error.cpp
        graphics/error.h
        res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Differential-equation
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Differential-equation SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Differential-equation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Differential-equation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

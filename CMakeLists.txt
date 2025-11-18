cmake_minimum_required(VERSION 3.16)

project(textEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 统一查找 Qt Widgets 组件（兼容 Qt5/Qt6）
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 统一管理所有源文件
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    aboutdialog.h
    aboutdialog.cpp
    aboutdialog.ui
    finddialog.h
    finddialog.cpp
    finddialog.ui
    replacedialog.h
    replacedialog.cpp
    replacedialog.ui
    codeeditor.h
    codeeditor.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(textEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(textEditor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(textEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 链接 Qt Widgets 库（兼容 Qt5/Qt6）
target_link_libraries(textEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 添加头文件搜索路径（关键：确保编译器能找到所有自定义头文件）
target_include_directories(textEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 平台相关配置（保持不变）
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.textEditor)
endif()
set_target_properties(textEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS textEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(textEditor)
endif()

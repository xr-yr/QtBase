cmake_minimum_required(VERSION 3.25)
project(QtBase)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

enable_testing()

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")
set(OpenCV_DIR "D:/work/openCV64")

file(GLOB SigSlotFiles CONFIGURE_DEPENDS 01.defSigSlot/*.cpp 01.defSigSlot/*.h 01.defSigSlot/*.ui)

file(GLOB CalcFiles CONFIGURE_DEPENDS 02.Calc/*.cpp 02.Calc/*.h 02.Calc/*.ui)

file(GLOB ImageFiles CONFIGURE_DEPENDS 03.openCVImage/*.cpp 03.openCVImage/*.h 03.openCVImage/*.ui)

file(GLOB SignalFiles CONFIGURE_DEPENDS 04.threadBase/*.cpp 04.threadBase/*.h 04.threadBase/*.ui)

file(GLOB NetWorkFiles CONFIGURE_DEPENDS 05.Network/*.cpp 05.Network/*.h 05.Network/*.ui)

add_subdirectory(test)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

find_package(OpenCV REQUIRED)

add_executable(QtBase main.cpp MainWidget.cpp MainWidget.h
        ${SigSlotFiles}
        ${CalcFiles}
        ${ImageFiles}
        ${SignalFiles}
        ${NetWorkFiles}
        )
target_link_libraries(QtBase
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        ${OpenCV_LIBS}
        )

target_include_directories(QtBase PUBLIC ${CMAKE_BINARY_DIR}/QtBase_autogen)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

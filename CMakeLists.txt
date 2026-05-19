cmake_minimum_required(VERSION 3.16)

project(cutebmoapi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Qml Quick WebSockets OpenApiCommon OpenApiTools)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_library(bmbase STATIC bmbase.h bmbase.cpp)

target_include_directories(bmbase PRIVATE Qt6::Quick Qt6::OpenApiCommon )
target_link_libraries(bmbase PRIVATE Qt6::Quick Qt6::WebSockets Qt6::OpenApiCommon )

add_subdirectory(camera)
add_subdirectory(webpresenter)
add_subdirectory(hyperdeck)

qt_add_executable(cutebmoapi
    main.cpp
)
qt_add_qml_module(cutebmoapi
    URI oatest
    QML_FILES
    Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(cutebmoapi PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appoatest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(cutebmoapi PRIVATE
    Qt6::Quick Qt6::WebSockets
    hyperdeck_apiplugin
    camera_apiplugin
    webpresenter_apiplugin
    )

install(TARGETS cutebmoapi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

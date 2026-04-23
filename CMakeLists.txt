cmake_minimum_required(VERSION 3.16)

project(hyperopenapitest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets OpenApiCommon OpenApiTools)

qt_standard_project_setup(REQUIRES 6.11)

add_subdirectory(cameraapi)

qt_add_executable(hyperopenapitest
    hyperdeckapi.h hyperdeckapi.cpp
    #cameraapi.h cameraapi.cpp
    main.cpp
)

qt_add_library(hyperdeckClientLibrary)
qt_add_openapi_client(hyperdeckClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/hyperdeck/HyperDeckRESTControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/hyperdeck_api/
)

qt_add_qml_module(hyperopenapitest
    URI oatest
    QML_FILES
    Main.qml
    SOURCES clipmodel.h clipmodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(hyperopenapitest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appoatest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(hyperopenapitest PRIVATE
    Qt6::Quick Qt6::WebSockets
    hyperdeckClientLibrary
    libCameraAPI
    )

install(TARGETS hyperopenapitest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.16)

project(hyperopenapitest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets OpenApiCommon OpenApiTools)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_executable(hyperopenapitest
    hyperdeckapi.h hyperdeckapi.cpp
    main.cpp
)

qt_add_library(hyperdeckClientLibrary)
qt_add_openapi_client(hyperdeckClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/hyperdeck/HyperDeckRESTControl.yaml)

qt_add_library(cameraSystemClientLibrary)
qt_add_openapi_client(cameraSystemClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/SystemControl.yaml)

qt_add_library(cameraEventClientLibrary)
qt_add_openapi_client(cameraEventClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/EventControl.yaml)

qt_add_library(cameraAudioClientLibrary)
qt_add_openapi_client(cameraAudioClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/AudioControl.yaml)

qt_add_library(cameraCCClientLibrary)
qt_add_openapi_client(cameraCCClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/ColorCorrectionControl.yaml)

qt_add_library(cameraLensClientLibrary)
qt_add_openapi_client(cameraLensClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/LensControl.yaml)

qt_add_library(cameraMediaClientLibrary)
qt_add_openapi_client(cameraMediaClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/MediaControl.yaml)

qt_add_library(cameraPresetClientLibrary)
qt_add_openapi_client(cameraPresetClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/PresetControl.yaml)

qt_add_library(cameraTimelineClientLibrary)
qt_add_openapi_client(cameraTimelineClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/TimelineControl.yaml)

qt_add_library(cameraTransportClientLibrary)
qt_add_openapi_client(cameraTransportClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/TransportControl.yaml)

qt_add_library(cameraVideoClientLibrary)
qt_add_openapi_client(cameraVideoClientLibrary SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/VideoControl.yaml)

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
    cameraSystemClientLibrary
    cameraEventClientLibrary
    cameraAudioClientLibrary
    cameraCCClientLibrary
    cameraLensClientLibrary
    cameraMediaClientLibrary
    cameraPresetClientLibrary
    cameraTimelineClientLibrary
    cameraTransportClientLibrary
    cameraVideoClientLibrary)

install(TARGETS hyperopenapitest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

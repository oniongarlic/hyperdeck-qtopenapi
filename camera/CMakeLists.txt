cmake_minimum_required(VERSION 3.16)

project(camera_api VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS WebSockets OpenApiCommon OpenApiTools)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_library(cameraSystemClientLibrary)
qt_add_openapi_client(cameraSystemClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/SystemControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_system_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/camera_system_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMCamera
    GENERATE_OPTIONS --api-name-suffix CameraSystemApi
)

qt_add_library(cameraEventClientLibrary)
qt_add_openapi_client(cameraEventClientLibrary
     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/EventControl.yaml
     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_event_api/
     OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/camera_event_api/
     ADDITIONAL_PROPERTIES cppNamespace=BMCamera
     GENERATE_OPTIONS --api-name-suffix CameraEventApi
)

#qt_add_library(cameraAudioClientLibrary)
#qt_add_openapi_client(cameraAudioClientLibrary
#    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/AudioControl.yaml
#    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_audio_api/
#)

# qt_add_library(cameraCCClientLibrary)
# qt_add_openapi_client(cameraCCClientLibrary
#     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/ColorCorrectionControl.yaml
#     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_cc_api/
# )

# qt_add_library(cameraLensClientLibrary)
# qt_add_openapi_client(cameraLensClientLibrary
#     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/LensControl.yaml
#     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_lens_api/
# )

# qt_add_library(cameraMediaClientLibrary)
# qt_add_openapi_client(cameraMediaClientLibrary
#     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/MediaControl.yaml
#     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_media_api/
# )

# qt_add_library(cameraPresetClientLibrary)
# qt_add_openapi_client(cameraPresetClientLibrary
#     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/PresetControl.yaml
#     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_preset_api/
# )

# qt_add_library(cameraTimelineClientLibrary)
# qt_add_openapi_client(cameraTimelineClientLibrary
#     SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/TimelineControl.yaml
#     OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_timeline_api/
# )

qt_add_library(cameraTransportClientLibrary)
qt_add_openapi_client(cameraTransportClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/TransportControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_transport_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/camera_transport_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMCamera
    GENERATE_OPTIONS --api-name-suffix CameraTransportApi
)

qt_add_library(cameraVideoClientLibrary)
qt_add_openapi_client(cameraVideoClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/camera/VideoControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/camera_video_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/camera_video_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMCamera
    GENERATE_OPTIONS --api-name-suffix CameraVideoApi
)

qt_add_library(camera_api STATIC)
qt_add_qml_module(camera_api
    URI org.tal.camera
    SOURCES cameraapi.h cameraapi.cpp camerasystemapi.h camerasystemapi.cpp
)

target_include_directories(camera_api INTERFACE bmbase)

target_link_libraries(camera_api PRIVATE
    Qt6::Quick Qt6::WebSockets
    bmbase
    cameraSystemClientLibrary
    cameraEventClientLibrary
    #cameraAudioClientLibrary
    #cameraCCClientLibrary
    #cameraLensClientLibrary
    #cameraMediaClientLibrary
    #cameraPresetClientLibrary
    #cameraTimelineClientLibrary
    cameraTransportClientLibrary
    cameraVideoClientLibrary
)

target_compile_definitions(camera_api PRIVATE CAMERAAPI_LIBRARY)


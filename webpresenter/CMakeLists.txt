cmake_minimum_required(VERSION 3.16)

project(webpresenter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets OpenApiCommon OpenApiTools)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_library(webpresenterSystemClientLibrary)
qt_add_openapi_client(webpresenterSystemClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/SystemControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_system_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_system_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMWebpresenter
    GENERATE_OPTIONS --api-name-suffix WebpresenterSystemApi
)

qt_add_library(webpresenterEventClientLibrary)
qt_add_openapi_client(webpresenterEventClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EventControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_event_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_event_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMWebpresenter
    GENERATE_OPTIONS --api-name-suffix WebpresenterEventApi
)

#qt_add_library(webpresenterLivestreamClientLibrary)
#qt_add_openapi_client(webpresenterLivestreamClientLibrary
#    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/LivestreamControl.yaml
#    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_livestream_api/
#    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/webpresenter_livestream_api/
#    ADDITIONAL_PROPERTIES cppNamespace=BMWebpresenter
#    GENERATE_OPTIONS --api-name-suffix WebpresenterLivestreamApi
#)

#target_include_directories(webpresenter INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
#
#target_link_libraries(webpresenter PRIVATE
#    Qt6::Quick Qt6::WebSockets
#    webpresenterSystemClientLibrary
#)
#
#target_compile_definitions(webpresenter PRIVATE WEBPRESENTER_LIBRARY)


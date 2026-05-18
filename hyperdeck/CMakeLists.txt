cmake_minimum_required(VERSION 3.16)

project(hyperdeck VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS OpenApiCommon OpenApiTools)

qt_add_library(hyperdeckClientLibrary)
qt_add_openapi_client(hyperdeckClientLibrary
    SPEC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/hyperdeck/HyperDeckRESTControl.yaml
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/hyperdeck_api/
    OUTPUT_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/hyperdeck_api/
    ADDITIONAL_PROPERTIES cppNamespace=BMHyperdeck
    GENERATE_OPTIONS --api-name-suffix HyperdeckApi
)

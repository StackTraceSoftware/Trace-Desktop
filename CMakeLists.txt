cmake_minimum_required(VERSION 3.5)

project(Trace-Desktop VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Widgets Network QuickWidgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/auth
    ${CMAKE_SOURCE_DIR}/auth/log-in
    ${CMAKE_SOURCE_DIR}/auth/registration
    ${CMAKE_SOURCE_DIR}/src/ui
)

set(SOURCES
    main.cpp
    src/auth/auth.cpp
    src/auth/registration/registration.cpp
    src/auth/log-in/log_in.cpp
)

set(UIS
    src/auth/registration/registration_window.ui
    src/auth/log-in/log_in_window.ui
)


add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${UIS}
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Network)

target_sources(Trace-Desktop
  PRIVATE
    .gitignore
)

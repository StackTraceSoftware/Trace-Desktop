cmake_minimum_required(VERSION 3.5)

project(Trace-Desktop VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)
find_package(Boost 1.86.0 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui_forms)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
        main.cpp
        src/auth/auth.cpp
        src/auth/registration/registration.cpp
        src/auth/log-in/log_in.cpp
        ui_forms/log_in_window.ui
        ui_forms/registration_window.ui
        include/auth/registration/registration.h
        include/auth/log-in/log_in.h
        include/auth/auth.h
        utils/config_utils.cpp
        include/utils/config_utils.h
        ui_forms/chats_window.ui
        include/chats/chats_window.h
        src/chats/chats_window.cpp
        include/utils/custom_windows.h
        utils/custom_windows.cpp
        src/chats/chat_cell.cpp
        include/chats/chat_cell.h
)

set(RESOURCE_FILES
        resources.qrc
        ui_forms/chat_cell.ui
)


add_executable(
        ${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} ${Boost_INCLUDE_DIRS} Qt6::Widgets Qt6::Network)

target_sources(Trace-Desktop
        PRIVATE
        .gitignore
)

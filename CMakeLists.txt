cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME "CKB_Test")
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Gui Svg)

# Добавляем сабпроекты для сервера и клиента
add_subdirectory(Server)
add_subdirectory(Client)

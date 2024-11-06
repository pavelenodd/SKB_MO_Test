cmake_minimum_required(VERSION 3.30)

set (PROJECT_NAME "CKB_Test")
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX) 
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)  


find_package(Qt6 REQUIRED COMPONENTS Core Network)


add_executable(${PROJECT_NAME} 
    Src/main.cpp
    )

target_sources(${PROJECT_NAME} PRIVATE
    Src/Server/server.cpp
    Src/Server/server.h
    
    Src/Client/client.cpp
    Src/Client/client.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Network)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
)

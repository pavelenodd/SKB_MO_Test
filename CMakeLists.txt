cmake_minimum_required(VERSION 3.30)

set (PROJECT_NAME "CKB_Test")
project(${PROJECT_NAME} VERSION 0.0.1)
 
add_executable(${PROJECT_NAME} 
    Src/main.cpp
    
    )

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# CMakeLists.txt для Server

add_executable(Server
    Src/main.cpp
    Src/server.cpp
    Src/server.h
    Src/GUI/server_gui.cpp
    Src/GUI/server_gui.h
)
# Указываем, что требуется обработать UI файл
set(UI_FILES
    Src/GUI/server.ui
)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# Добавляем заголовки и исходные файлы UI
target_sources(Server PRIVATE
    ${UI_HEADERS}
)

# Указываем директорию для сгенерированных файлов и подключения заголовков
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_BINARY_DIR} Src/GUI)

target_link_libraries(Server PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)

# Включаем автоматическую генерацию MOC-файлов
set_target_properties(Server PROPERTIES AUTOMOC ON)

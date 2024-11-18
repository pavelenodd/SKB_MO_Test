# CMakeLists.txt для Client

add_executable(Client
    Src/main.cpp
    Src/client.cpp
    Src/client.h
    Src/GUI/client_gui.cpp
    Src/GUI/client_gui.h
)

# Указываем, что требуется обработать UI файл
set(UI_FILES
    Src/GUI/client.ui
)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# Добавляем заголовки и исходные файлы UI
target_sources(Client PRIVATE
    ${UI_HEADERS}
)

# Указываем директорию для сгенерированных файлов и подключения заголовков
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_BINARY_DIR} Src/GUI)

target_link_libraries(Client PRIVATE Qt6::Core Qt6::Network Qt6::Widgets Qt6::Svg Qt6::Gui)

# Включаем автоматическую генерацию MOC-файлов
set_target_properties(Client PROPERTIES AUTOMOC ON)

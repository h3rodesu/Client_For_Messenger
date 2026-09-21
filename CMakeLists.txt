cmake_minimum_required(VERSION 3.15)
project(ChatClient VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)
set(SOURCES
    client.cpp
    Receive.cpp
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_dx11.cpp
    imgui_impl_win32.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

set(HEADERS
    Receive.h
    imconfig.h
    imgui.h
    imgui_impl_dx11.h
    imgui_impl_win32.h
    imgui_internal.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    httplib.h
    MediaClient.h
    stb_image.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
if(WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ws2_32
        d3d11
        d3dcompiler
        dxgi
    )
 set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/MANIFESTDEPENDENCY:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""
    )
endif()
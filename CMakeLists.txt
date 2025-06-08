cmake_minimum_required(VERSION 3.10)
project(Pacman)

# C++17 verwenden
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pfade zu Raylib
set(RAYLIB_ROOT "C:/raylib/raylib")
include_directories(${RAYLIB_ROOT}/src)
link_directories(${RAYLIB_ROOT}/build/raylib)

# Pfad zu miniaudio (angenommen liegt unter libs/miniaudio)
include_directories(${CMAKE_SOURCE_DIR}./miniaudio)

# Quelldateien suchen
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/*.cpp"
)

# Build-Ordner-Dateien rausfiltern
foreach(file ${SOURCES})
    string(FIND "${file}" "${CMAKE_BINARY_DIR}" EXCLUDE_POS)
    if(NOT EXCLUDE_POS EQUAL -1)
        list(REMOVE_ITEM SOURCES "${file}")
    endif()
endforeach()

# Erstelle das Executable
add_executable(Pacman ${SOURCES})

# Raylib und Windows-Bibliotheken linken
target_link_libraries(Pacman 
    raylib
    winmm
    gdi32
    opengl32
    kernel32
    user32
    winspool
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)
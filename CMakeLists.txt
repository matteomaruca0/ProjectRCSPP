cmake_minimum_required(VERSION 3.20)

# Imposta i compilatori GCC da Homebrew se disponibili (supportano OpenMP su macOS)
if(EXISTS "/opt/homebrew/bin/gcc-16" AND NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-16)
endif()
if(EXISTS "/opt/homebrew/bin/g++-16" AND NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-16)
endif()

project(ProgettoRCSPP CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Percorso alla libreria PathWyse presente nel workspace
set(PW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pathwyse-1.0.0)

# Verifica la presenza della libreria compilata libpathwyse_core.dylib
if(NOT EXISTS "${PW_DIR}/bin/libpathwyse_core.dylib")
    message(WARNING "Attenzione: ${PW_DIR}/bin/libpathwyse_core.dylib non trovata. Esegui la compilazione dentro pathwyse-1.0.0 prima di compilare il progetto.")
endif()

# Definizione del target della libreria PathWyse (shared library precompilata)
add_library(pathwyse_core SHARED IMPORTED)
set_target_properties(pathwyse_core PROPERTIES
    IMPORTED_LOCATION "${PW_DIR}/bin/libpathwyse_core.dylib"
    INTERFACE_INCLUDE_DIRECTORIES "${PW_DIR}/src/core"
)

# Eseguibile di prova
add_executable(progetto_test src/main.cpp)
target_link_libraries(progetto_test PRIVATE pathwyse_core)

# Flag per OpenMP (necessario per PathWyse)
target_compile_options(progetto_test PRIVATE -fopenmp)
target_link_options(progetto_test PRIVATE -fopenmp)

# Configurazione RPATH per trovare la dylib a runtime ovunque venga eseguito il binario
set_target_properties(progetto_test PROPERTIES
    BUILD_RPATH "${PW_DIR}/bin"
    INSTALL_RPATH "${PW_DIR}/bin"
)

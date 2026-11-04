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

# Configurazione RPATH per trovare la dylib a runtime ovunque venga eseguito il binario
set_target_properties(progetto_test PROPERTIES
    BUILD_RPATH "${PW_DIR}/bin"
    INSTALL_RPATH "${PW_DIR}/bin"
)

# File main
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE pathwyse_core)
target_compile_options(main PRIVATE -fopenmp)
target_link_options(main PRIVATE -fopenmp)
set_target_properties(main PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#File tutorial
add_executable(ese1 tutorial_cpp/es1_hello.cpp)
target_link_libraries(ese1 PRIVATE pathwyse_core)
target_compile_options(ese1 PRIVATE -fopenmp)
target_link_options(ese1 PRIVATE -fopenmp)
set_target_properties(ese1 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese2
add_executable(ese2 tutorial_cpp/es2_inspect.cpp)
target_link_libraries(ese2 PRIVATE pathwyse_core)
target_compile_options(ese2 PRIVATE -fopenmp)
target_link_options(ese2 PRIVATE -fopenmp)
set_target_properties(ese2 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese2mio tutorial_cpp/es2_mio.cpp)
target_link_libraries(ese2mio PRIVATE pathwyse_core)
target_compile_options(ese2mio PRIVATE -fopenmp)
target_link_options(ese2mio PRIVATE -fopenmp)
set_target_properties(ese2mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese3
add_executable(ese3 tutorial_cpp/es3_solution.cpp)
target_link_libraries(ese3 PRIVATE pathwyse_core)
target_compile_options(ese3 PRIVATE -fopenmp)
target_link_options(ese3 PRIVATE -fopenmp)
set_target_properties(ese3 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese3mio tutorial_cpp/es3_mio.cpp)
target_link_libraries(ese3mio PRIVATE pathwyse_core)
target_compile_options(ese3mio PRIVATE -fopenmp)
target_link_options(ese3mio PRIVATE -fopenmp)
set_target_properties(ese3mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese4
add_executable(ese4 tutorial_cpp/es4_build.cpp)
target_link_libraries(ese4 PRIVATE pathwyse_core)
target_compile_options(ese4 PRIVATE -fopenmp)
target_link_options(ese4 PRIVATE -fopenmp)
set_target_properties(ese4 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese4mio tutorial_cpp/es4_mio.cpp)
target_link_libraries(ese4mio PRIVATE pathwyse_core)
target_compile_options(ese4mio PRIVATE -fopenmp)
target_link_options(ese4mio PRIVATE -fopenmp)
set_target_properties(ese4mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese5
add_executable(ese5 tutorial_cpp/es5_bounds.cpp)
target_link_libraries(ese5 PRIVATE pathwyse_core)
target_compile_options(ese5 PRIVATE -fopenmp)
target_link_options(ese5 PRIVATE -fopenmp)
set_target_properties(ese5 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese5mio tutorial_cpp/es5_mio.cpp)
target_link_libraries(ese5mio PRIVATE pathwyse_core)
target_compile_options(ese5mio PRIVATE -fopenmp)
target_link_options(ese5mio PRIVATE -fopenmp)
set_target_properties(ese5mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese6
add_executable(ese6 tutorial_cpp/es6_algorithms.cpp)
target_link_libraries(ese6 PRIVATE pathwyse_core)
target_compile_options(ese6 PRIVATE -fopenmp)
target_link_options(ese6 PRIVATE -fopenmp)
set_target_properties(ese6 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese6mio tutorial_cpp/es6_mio.cpp)
target_link_libraries(ese6mio PRIVATE pathwyse_core)
target_compile_options(ese6mio PRIVATE -fopenmp)
target_link_options(ese6mio PRIVATE -fopenmp)
set_target_properties(ese6mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese6b tutorial_cpp/es6b_pool.cpp)
target_link_libraries(ese6b PRIVATE pathwyse_core)
target_compile_options(ese6b PRIVATE -fopenmp)
target_link_options(ese6b PRIVATE -fopenmp)
set_target_properties(ese6b PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese6bmio tutorial_cpp/es6b_mio.cpp)
target_link_libraries(ese6bmio PRIVATE pathwyse_core)
target_compile_options(ese6bmio PRIVATE -fopenmp)
target_link_options(ese6bmio PRIVATE -fopenmp)
set_target_properties(ese6bmio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

#Ese7
add_executable(ese7 tutorial_cpp/es7_two_resources.cpp)
target_link_libraries(ese7 PRIVATE pathwyse_core)
target_compile_options(ese7 PRIVATE -fopenmp)
target_link_options(ese7 PRIVATE -fopenmp)
set_target_properties(ese7 PROPERTIES BUILD_RPATH "${PW_DIR}/bin")

add_executable(ese7mio tutorial_cpp/es7_mio.cpp)
target_link_libraries(ese7mio PRIVATE pathwyse_core)
target_compile_options(ese7mio PRIVATE -fopenmp)
target_link_options(ese7mio PRIVATE -fopenmp)
set_target_properties(ese7mio PROPERTIES BUILD_RPATH "${PW_DIR}/bin")
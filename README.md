# Progetto RCSPP con PathWyse

Guida rapida per creare nuovi file sorgente e compilare il progetto.

---

## 1. Come creare un nuovo file

### Opzione A: Aggiungere classi/funzioni al progetto esistente
1. Crea i tuoi file header e sorgente dentro la cartella `src/` (es. `src/mio_algoritmo.h` e `src/mio_algoritmo.cpp`).
2. Apri `CMakeLists.txt` e aggiungi il file `.cpp` al target `progetto_test`:
   ```cmake
   add_executable(progetto_test 
       src/main.cpp
       src/mio_algoritmo.cpp
   )
   ```

### Opzione B: Creare un nuovo eseguibile indipendente
1. Crea il nuovo file sorgente (es. `src/nuovo_test.cpp`).
2. In fondo a `CMakeLists.txt`, aggiungi:
   ```cmake
   add_executable(nuovo_test src/nuovo_test.cpp)
   target_link_libraries(nuovo_test PRIVATE pathwyse_core)
   target_compile_options(nuovo_test PRIVATE -fopenmp)
   target_link_options(nuovo_test PRIVATE -fopenmp)
   set_target_properties(nuovo_test PROPERTIES BUILD_RPATH "${PW_DIR}/bin")
   ```

---

## 2. Come compilare ed eseguire

### Da Terminale
```bash
# Compilazione (dalla cartella principale del progetto):
cmake --build build

# Se aggiungi un nuovo file o modifichi CMakeLists.txt, riconfigura con:
cmake -B build -S . && cmake --build build

# Esecuzione:
./build/progetto_test
```

### Da VS Code
- **Compilazione rapida**: premi `Cmd + Shift + B`.
- **Esecuzione / Debug**: premi `F5`.

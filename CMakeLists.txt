cmake_minimum_required(VERSION 3.10)
project(indolang C)

# Gunakan standar C11
set(CMAKE_C_STANDARD 11)

# Daftar semua file sumber
set(SOURCES
        main.c
        parser.c
        runtime.c
        evaluator.c
)

# Buat executable bernama 'indo'
add_executable(indo ${SOURCES})

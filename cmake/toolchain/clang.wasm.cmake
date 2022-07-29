##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##
## emcmake cmake .. -G Ninja  -DCMAKE_TOOLCHAIN_FILE='../cmake/toolchain/emcc.cmake'
##
##==================================================================================================
set(CMAKE_C_COMPILER    emcc )
set(CMAKE_CXX_COMPILER  em++ )

set(CMAKE_CXX_FLAGS     "-DEVE_NO_FORCEINLINE ${EVE_OPTIONS} -fexceptions -msimd128" )
set(CMAKE_EXE_LINKER_FLAGS  "-s WASM_BIGINT -s WASM=1 ")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(ECMASCRIPT_ROOT get_filename_component(${CMAKE_CXX_COMPILER}))

set(CMAKE_FIND_ROOT_PATH "$ENV{EMSDK}/upstream/emscripten/cache/sysroot/")

set(CMAKE_CROSSCOMPILING_CMD ${PROJECT_SOURCE_DIR}/cmake/toolchain/run_wasm.sh     )

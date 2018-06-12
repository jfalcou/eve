##==================================================================================================
##  EVE - Expressive Vector Engine
##  From https://github.com/Crascit/DownloadProject
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(_DownloadProjectDir "${CMAKE_CURRENT_LIST_DIR}")

include(CMakeParseArguments)

function(download_project)

    set(options QUIET)
    set(oneValueArgs
        PROJ
        PREFIX
        DOWNLOAD_DIR
        SOURCE_DIR
        BINARY_DIR
        # Prevent the following from being passed through
        CONFIGURE_COMMAND
        BUILD_COMMAND
        INSTALL_COMMAND
        TEST_COMMAND
    )
    set(multiValueArgs "")

    cmake_parse_arguments(DL_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Hide output if requested
    if (DL_ARGS_QUIET)
        set(OUTPUT_QUIET "OUTPUT_QUIET")
    else()
        unset(OUTPUT_QUIET)
        message(STATUS "Downloading/updating ${DL_ARGS_PROJ}")
    endif()

    # Set up where we will put our temporary CMakeLists.txt file and also
    # the base point below which the default source and binary dirs will be
    if (NOT DL_ARGS_PREFIX)
        set(DL_ARGS_PREFIX "${CMAKE_BINARY_DIR}")
    endif()
    if (NOT DL_ARGS_DOWNLOAD_DIR)
        set(DL_ARGS_DOWNLOAD_DIR "${DL_ARGS_PREFIX}/${DL_ARGS_PROJ}-download")
    endif()

    # Ensure the caller can know where to find the source and build directories
    if (NOT DL_ARGS_SOURCE_DIR)
        set(DL_ARGS_SOURCE_DIR "${DL_ARGS_PREFIX}/${DL_ARGS_PROJ}-src")
    endif()
    if (NOT DL_ARGS_BINARY_DIR)
        set(DL_ARGS_BINARY_DIR "${DL_ARGS_PREFIX}/${DL_ARGS_PROJ}-build")
    endif()
    set(${DL_ARGS_PROJ}_SOURCE_DIR "${DL_ARGS_SOURCE_DIR}" PARENT_SCOPE)
    set(${DL_ARGS_PROJ}_BINARY_DIR "${DL_ARGS_BINARY_DIR}" PARENT_SCOPE)

    # Create and build a separate CMake project to carry out the download.
    # If we've already previously done these steps, they will not cause
    # anything to be updated, so extra rebuilds of the project won't occur.

   configure_file("${_DownloadProjectDir}/download.CMakeLists.cmake.in"
                   "${DL_ARGS_DOWNLOAD_DIR}/CMakeLists.txt")

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    #${OUTPUT_QUIET}
                    WORKING_DIRECTORY "${DL_ARGS_DOWNLOAD_DIR}"
    )
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    ${OUTPUT_QUIET}
                    WORKING_DIRECTORY "${DL_ARGS_DOWNLOAD_DIR}"
    )

endfunction()

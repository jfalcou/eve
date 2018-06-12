##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup the documentation
##==================================================================================================
find_package(Sphinx)

if(SPHINX_FOUND)
    message(STATUS "[eve] Sphinx found - Enabling documentation")
    set(SPHINX_THEME sphinx_rtd_theme)

    # set(SPHINX_OPTIONS
    #                      "\"textcolor\": \"rgb(0,0,255)\"
    #                     , \"headingcolor\": \"rgb(0,0,255)\""
    #                     , \"headingcolor\": \"rgb(0,0,255)\""
    #                     , \"headingcolor\": \"rgb(0,0,255)\""
    #                     , \"headingcolor\": \"rgb(0,0,255)\""
    #    )

    set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")
    set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")
    set(SPHINX_HTML_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/html")

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in"
        "${BINARY_BUILD_DIR}/conf.py"
        @ONLY)

    add_custom_target ( doc ALL ${SPHINX_EXECUTABLE}
                                -q -b html
                                -c "${BINARY_BUILD_DIR}"
                                -d "${SPHINX_CACHE_DIR}"
                                "${CMAKE_CURRENT_SOURCE_DIR}"
                                "${SPHINX_HTML_DIR}"
                        COMMENT "Building HTML documentation with Sphinx"
                      )
else()
    message(STATUS "[eve] Sphinx not found - Disabling documentation")
endif()

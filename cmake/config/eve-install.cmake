##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(GNUInstallDirs)
set(MAIN_DEST     "${CMAKE_INSTALL_LIBDIR}/eve")
set(INSTALL_DEST  "${CMAKE_INSTALL_INCLUDEDIR}")
set(DOC_DEST      "${CMAKE_INSTALL_DOCDIR}")

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(eve_lib INTERFACE)
target_include_directories( eve_lib INTERFACE
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${INSTALL_DEST}>
                          )
target_compile_features(eve_lib INTERFACE cxx_std_20)
set_target_properties(eve_lib PROPERTIES EXPORT_NAME eve)
add_library(eve::eve ALIAS eve_lib)

## =================================================================================================
## Install target with versioned folder
## =================================================================================================
install(TARGETS   eve_lib EXPORT eve_export_set DESTINATION "${MAIN_DEST}")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/eve               DESTINATION "${INSTALL_DEST}" )
install(FILES     ${PROJECT_SOURCE_DIR}/cmake/eve-config.cmake    DESTINATION "${MAIN_DEST}"    )
install(FILES     ${PROJECT_SOURCE_DIR}/cmake/eve-multiarch.cmake DESTINATION "${MAIN_DEST}"    )
install(FILES     ${PROJECT_SOURCE_DIR}/LICENSE.md                DESTINATION "${DOC_DEST}"     )
install(EXPORT    eve_export_set NAMESPACE "eve::" DESTINATION "${MAIN_DEST}")

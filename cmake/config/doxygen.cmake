##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Add Doxygen building target
##==================================================================================================
if (DOXYGEN_FOUND)
  set(DOXYGEN_CONFIG ${PROJECT_SOURCE_DIR}/doc/Doxyfile)
  add_custom_target ( doxygen
                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                      COMMENT "[eve] Generating API documentation with Doxygen"
                      VERBATIM
                    )
endif (DOXYGEN_FOUND)

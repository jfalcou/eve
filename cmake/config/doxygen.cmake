##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Find Doxygen
##==================================================================================================
find_package(Doxygen)

if (DOXYGEN_FOUND)
  message( STATUS "[eve] Doxygen available")
else (DOXYGEN_FOUND)
  message( STATUS "[eve] Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

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

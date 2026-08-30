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

  ## Doxygen never fetches anything itself, so kumi's tagfile has to be on disk before the target
  ## runs. The Doxyfile reaches it through $(EVE_DOXYGEN_OUPUT). Without it the kumi:: references
  ## stay unresolved.
  file( DOWNLOAD "https://jfalcou.github.io/kumi/kumi.tag" "${PROJECT_BINARY_DIR}/kumi.tag"
        STATUS KUMI_TAG_STATUS
      )
  list(GET KUMI_TAG_STATUS 0 KUMI_TAG_CODE)
  if(NOT KUMI_TAG_CODE EQUAL 0)
    message(WARNING "[eve] - kumi.tag could not be fetched (${KUMI_TAG_STATUS}), the kumi:: links will be dead")
  endif()

  add_custom_target ( doxygen
                      COMMAND EVE_DOXYGEN_OUPUT=${PROJECT_BINARY_DIR}/docs ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                      COMMENT "[eve] Generating API documentation with Doxygen - Local version"
                      VERBATIM
                    )
endif (DOXYGEN_FOUND)

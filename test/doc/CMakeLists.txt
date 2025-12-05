##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
add_custom_target(doc.exe )
set(doc_root "${PROJECT_SOURCE_DIR}/test/doc")

##==================================================================================================
## GLOB and process algo doc tests
##==================================================================================================
add_custom_target(doc.pipo.exe        )
add_dependencies(doc.exe doc.pipo.exe )
glob_unit("doc" ${doc_root} "pipo/*.cpp")

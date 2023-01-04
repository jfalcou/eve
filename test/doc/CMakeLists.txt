##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
add_custom_target(doc.exe )
set(doc_root "${CMAKE_SOURCE_DIR}/test/doc")

##==================================================================================================
## GLOB and process algo doc tests
##==================================================================================================
add_custom_target(doc.algo.exe        )
add_dependencies(doc.exe doc.algo.exe )
glob_unit("doc" ${doc_root} "algo/*.cpp")

##==================================================================================================
## GLOB and process bessel doc tests
##==================================================================================================
add_custom_target(doc.bessel.exe        )
add_dependencies(doc.exe doc.bessel.exe )
glob_unit("doc" ${doc_root} "bessel/regular/*.cpp")

##==================================================================================================
## GLOB and process combinatorial doc tests
##==================================================================================================
add_custom_target(doc.combinatorial.exe        )
add_dependencies(doc.exe doc.combinatorial.exe )
glob_unit("doc" ${doc_root} "combinatorial/regular/*.cpp"    )
glob_unit("doc" ${doc_root} "combinatorial/conversion/*.cpp" )

##==================================================================================================
## GLOB and process complex doc tests
##==================================================================================================
add_custom_target(doc.complex.exe        )
add_dependencies(doc.exe doc.complex.exe )
glob_unit("doc" ${doc_root} "complex/regular/*.cpp"  )
glob_unit("doc" ${doc_root} "complex/pedantic/*.cpp" )

##==================================================================================================
## GLOB and process core doc tests
##==================================================================================================
add_custom_target(doc.core.exe        )
add_dependencies(doc.exe doc.core.exe )
glob_unit("doc" ${doc_root} "core/constant/*.cpp"  )
glob_unit("doc" ${doc_root} "core/fuzzy/*.cpp"     )
glob_unit("doc" ${doc_root} "core/masked/*.cpp"    )
glob_unit("doc" ${doc_root} "core/pedantic/*.cpp"  )
glob_unit("doc" ${doc_root} "core/raw/*.cpp"       )
glob_unit("doc" ${doc_root} "core/regular/*.cpp"   )
glob_unit("doc" ${doc_root} "core/roundings/*.cpp" )
glob_unit("doc" ${doc_root} "core/saturated/*.cpp" )

##==================================================================================================
## GLOB and process elliptic doc tests
##==================================================================================================
add_custom_target(doc.elliptic.exe        )
add_dependencies(doc.exe doc.elliptic.exe )
glob_unit("doc" ${doc_root} "elliptic/regular/*.cpp")

##==================================================================================================
## GLOB and process math doc tests
##==================================================================================================
add_custom_target(doc.math.exe        )
add_dependencies(doc.exe doc.math.exe )
glob_unit("doc" ${doc_root} "math/pedantic/*.cpp" )
glob_unit("doc" ${doc_root} "math/masked/*.cpp"   )
glob_unit("doc" ${doc_root} "math/regular/*.cpp"  )

##==================================================================================================
## GLOB and process polynomial doc tests
##==================================================================================================
add_custom_target(doc.polynomial.exe        )
add_dependencies(doc.exe doc.polynomial.exe )
glob_unit("doc" ${doc_root} "polynomial/condon_shortley/*.cpp" )
glob_unit("doc" ${doc_root} "polynomial/kind/*.cpp"            )
glob_unit("doc" ${doc_root} "polynomial/regular/*.cpp"         )
glob_unit("doc" ${doc_root} "polynomial/sph/*.cpp"             )
glob_unit("doc" ${doc_root} "polynomial/successor/*.cpp"       )

##==================================================================================================
## GLOB and process special doc tests
##==================================================================================================
add_custom_target(doc.special.exe        )
add_dependencies(doc.exe doc.special.exe )
glob_unit("doc" ${doc_root} "special/pedantic/*.cpp" )
glob_unit("doc" ${doc_root} "special/raw/*.cpp"      )
glob_unit("doc" ${doc_root} "special/regular/*.cpp"  )

##==================================================================================================
## GLOB and process traits doc tests
##==================================================================================================
add_custom_target(doc.traits.exe        )
add_dependencies(doc.exe doc.traits.exe )
glob_unit("doc" ${doc_root} "traits/*.cpp")

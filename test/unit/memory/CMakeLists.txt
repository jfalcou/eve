##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.memory.exe       )
add_custom_target(unit.memory.scalar.exe)
add_custom_target(unit.memory.simd.exe  )

add_dependencies(unit.scalar.exe  unit.memory.scalar.exe)
add_dependencies(unit.simd.exe    unit.memory.simd.exe  )
add_dependencies(unit.memory.exe  unit.memory.scalar.exe)
add_dependencies(unit.memory.exe  unit.memory.simd.exe  )

##==================================================================================================
## Memory API tests
make_unit( "unit.memory" aligned_alloc.cpp                            )
make_unit( "unit.memory" aligned_allocator.cpp                        )
make_unit( "unit.memory" aligned_ptr.cpp                              )
make_unit( "unit.memory" is_aligned.cpp                               )
make_unit( "unit.memory" load/regular/aligned/arithmetic.cpp          )
make_unit( "unit.memory" load/regular/aligned/arithmetic_if.cpp       )
make_unit( "unit.memory" load/regular/aligned/arithmetic_if_else.cpp  )
make_unit( "unit.memory" load/regular/aligned/logical.cpp             )
make_unit( "unit.memory" load/regular/aligned/logical_if.cpp          )
make_unit( "unit.memory" load/regular/aligned/logical_if_else.cpp     )
make_unit( "unit.memory" load/regular/unaligned/arithmetic.cpp        )
make_unit( "unit.memory" load/regular/unaligned/arithmetic_if.cpp     )
make_unit( "unit.memory" load/regular/unaligned/arithmetic_if_else.cpp)
make_unit( "unit.memory" load/regular/unaligned/logical.cpp           )
make_unit( "unit.memory" load/regular/unaligned/logical_if.cpp        )
make_unit( "unit.memory" load/regular/unaligned/logical_if_else.cpp   )
make_unit( "unit.memory" compress_store.cpp                   )
make_unit( "unit.memory" store/aligned.cpp      )
make_unit( "unit.memory" store/conditional.cpp  )
make_unit( "unit.memory" store/tuple.cpp        )
make_unit( "unit.memory" store/unaligned.cpp    )

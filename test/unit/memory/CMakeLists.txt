##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.memory.exe )

##==================================================================================================
## Memory API tests
make_unit( "unit.memory" aligned_allocator.cpp                  )
make_unit( "unit.memory" aligned_ptr.cpp                        )
make_unit( "unit.memory" is_aligned.cpp                         )
make_unit( "unit.memory" load/aligned/arithmetic.cpp            )
make_unit( "unit.memory" load/aligned/arithmetic_if.cpp         )
make_unit( "unit.memory" load/aligned/arithmetic_if_else.cpp    )
make_unit( "unit.memory" load/aligned/logical.cpp               )
make_unit( "unit.memory" load/aligned/logical_if.cpp            )
make_unit( "unit.memory" load/aligned/logical_if_else.cpp       )
make_unit( "unit.memory" load/unaligned/arithmetic.cpp          )
make_unit( "unit.memory" load/unaligned/arithmetic_if.cpp       )
make_unit( "unit.memory" load/unaligned/arithmetic_if_else.cpp  )
make_unit( "unit.memory" load/unaligned/logical.cpp             )
make_unit( "unit.memory" load/unaligned/logical_if.cpp          )
make_unit( "unit.memory" load/unaligned/logical_if_else.cpp     )
make_unit( "unit.memory" load/tuple.cpp                         )
make_unit( "unit.memory" soa_ptr.cpp                            )
make_unit( "unit.memory" stack_buffer.cpp                       )
make_unit( "unit.memory" read.cpp                               )
make_unit( "unit.memory" store/aligned.cpp                      )
make_unit( "unit.memory" store/conditional.cpp                  )
make_unit( "unit.memory" store/tuple.cpp                        )
make_unit( "unit.memory" store/unaligned.cpp                    )
make_unit( "unit.memory" compress_store/logical.cpp             )
make_unit( "unit.memory" compress_store/tuple.cpp               )
make_unit( "unit.memory" compress_store/wide_diff_logicals.cpp  )
make_unit( "unit.memory" compress_store/wide.cpp                )
make_unit( "unit.memory" unalign.cpp                            )
make_unit( "unit.memory" write.cpp                              )

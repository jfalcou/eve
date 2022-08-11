##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Basic type roots
##==================================================================================================
set(real_types         double float                            )
set(int_types          int64 int32 int16 int8                  )
set(uint_types         uint64 uint32 uint16 uint8              )
set(integral_types     "${int_types};${uint_types}"            )
set(all_types          "${real_types};${integral_types}"       )
set(signed_types       "${real_types};${int_types}"            )
set(real_types_32      float                                   )
set(int_types_32       int32 int16 int8                        )
set(uint_types_32      uint32 uint16 uint8                     )
set(integral_types_32  "${int_types_32};${uint_types_32}"      )
set(all_types_32       "${real_types_32};${integral_types_32}" )
set(signed_types_32    "${real_types_32};${int_types_32}"      )
set(uint_or_real_types "${real_types};${uint_types}"           )
set(uint_or_real_types_32 "${real_types_32};${uint_types_32}"  )

macro(to_std type output)
  if(${type} MATCHES "^[u]?int[a-zA-Z]*")
    set(${output} "std::${type}_t")
  else()
    set(${output} "${type}")
  endif()
endmacro()

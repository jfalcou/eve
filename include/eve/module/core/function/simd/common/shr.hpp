//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto
  shr_(EVE_SUPPORTS(simd_), wide<T, N, aggregated_> const &v0, U const &v1) noexcept
  {
    return aggregate(eve::shr, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto
  shr_(EVE_SUPPORTS(simd_), wide<T, N, emulated_> const &v0, U const &v1) noexcept
  {
    return map(eve::shr, v0, v1);
  }
}

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // Infix support
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto
  operator >> (wide<T, N, ABI> const &v0, U const &v1) noexcept
  {
    return eve::shr(v0, v1);
  }
}


#endif

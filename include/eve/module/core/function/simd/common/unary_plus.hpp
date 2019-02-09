//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_UNARY_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_UNARY_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> unary_plus_(EVE_SUPPORTS(simd_),
                                                      wide<T, N, aggregated_> const &v) noexcept
  {
    return v;
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation  for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto unary_plus_(EVE_SUPPORTS(simd_), wide<T, N, emulated_> const &v0) noexcept
  {
    return v0;
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator+(wide<T, N, ABI> const &v) noexcept
  {
    return v;
  }
}

#endif

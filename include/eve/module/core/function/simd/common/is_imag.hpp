//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_IMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_IMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(simd_),
                               wide<T, N, ABI> const &v) noexcept
  {
    return is_eqz(v);
  }

  // -----------------------------------------------------------------------------------------------
  // logical
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(simd_),
                              wide<logical<T>, N, ABI> const &v) noexcept
  {
    return logical_not(v);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(simd_),
                               wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::is_imag, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_imag_(EVE_SUPPORTS(simd_)
                              , wide<T, N, emulated_> const &v0) noexcept
  {
    return map(eve::is_imag, v0);
  }
}

#endif

//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(simd_),
                               wide<T, N, ABI> const &v) noexcept
  {
    return is_not_equal(v, Zero(as(v)));
  }
  // -----------------------------------------------------------------------------------------------
  // logical
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(simd_),
                               wide<logical<T>, N, ABI> const &v) noexcept
  {
    return v;
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(simd_),
                               wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::is_nez, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_nez_(EVE_SUPPORTS(simd_)
                              , wide<T, N, emulated_> const &v0) noexcept
  {
    return map(eve::is_nez, v0);
  }
}


#endif

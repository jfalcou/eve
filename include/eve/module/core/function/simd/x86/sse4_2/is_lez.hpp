//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_2_IS_LEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_2_IS_LEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_eqz.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse4_2
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_lez_(EVE_SUPPORTS(sse4_2_), wide<std::int64_t, N, sse_> const &v0) noexcept
  {
    return logical_not(is_greater(v0, Zero(as(v0))));
  }
}

#endif

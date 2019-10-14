//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSHR_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/abs.hpp>
#include <eve/forward.hpp>
#include <type_traits>

#ifndef NDEBUG
#  include <eve/constant/zero.hpp>
#  include <eve/function/max.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  rshr_(EVE_SUPPORTS(cpu_), T const &v0, U const &v1) noexcept requires(T,
                                                                        vectorized<T>,
                                                                        integral<value_type_t<U>>,
                                                                        integral<value_type_t<T>>)
  {
    if constexpr(std::is_unsigned_v<value_type_t<U>>)
      return shl(v0, v1);
    else
    {
#ifndef NDEBUG
      return if_else(is_gtz(v1), shr(v0, max(Zero(as(v1)), v1)), shl(v0, max(Zero(as(v1)), -v1)));
#else
      return if_else(is_gtz(v1), shr(v0, v1), shl(v0, -v1));
#endif
    }
  }
}

#endif

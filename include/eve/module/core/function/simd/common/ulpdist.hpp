//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ULPDIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/dist.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE auto ulpdist_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  requires(
      std::conditional_t<is_vectorized_v<T>, T, U>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using vt_t =  value_type_t<T>; 
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto aa = eve::detail::bitinteger(a);
      auto bb = eve::detail::bitinteger(b);
      return if_else(numeric_(is_equal)(a, b), eve::zero_
                    , if_else (is_unordered(a, b)
                              , eve::allbits_
                              , convert(dist(bb, aa), as<vt_t>())
                              )/2
                    ); 
    }
    else
      return dist(a, b); 
  }
}

#endif

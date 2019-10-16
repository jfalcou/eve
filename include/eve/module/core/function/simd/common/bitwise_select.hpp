//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_andnot.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  bitwise_select_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept 
  requires( std::conditional_t<is_vectorized_v<V>, V, U>,
            bitwise_compatible<T,U>,bitwise_compatible<T,V>,
            detail::either<is_vectorized_v<V>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    using vt_t  = value_type_t<U>;
    using ut_t  = value_type_t<V>;

    if constexpr(!is_vectorized_v<V>)
    {
      return eve::bitwise_select(a, b, U(bitwise_cast(c,as_<ut_t>())));
    }
    else if constexpr(!is_vectorized_v<U>)
    {
      return eve::bitwise_select(a, V(bitwise_cast(b,as_<vt_t>())), c);
    }
    else
    {
      // here U and V are vectorized and are equal
      if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
      {
        return map(eve::bitwise_select, a, b, c);
      }
      else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
      {
        return aggregate(eve::bitwise_select, a, b, c);
      }
      else
      {
        return bitwise_or(bitwise_and(b, a), bitwise_andnot(c, a));
      }
    }
  }
}

#endif

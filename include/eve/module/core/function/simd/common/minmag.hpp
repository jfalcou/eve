//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MINMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MINMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/min.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular, pedantic or numeric
  template<typename Tag, typename T, typename U>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), Tag tag, T const &a, U const &b) noexcept
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    { return map(tag(eve::minmag), abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b)); }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(tag(eve::minmag), abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_Vectorized_v<T> && is_Vectorized_v<U>)
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr (std::is_same_v<Tag, numeric_type>)
        {
          auto aa = if_else(is_nan(a), b, a);
          auto bb = if_else(is_nan(b), a, b);
          auto z =  minmag(aa, bb);
          return z; 
        }
        else
        {
          auto aa = eve::abs(a);
          auto ab = eve::abs(b);
          return if_else(is_not_greater_equal(aa, ab),
                         a,
                         if_else(is_not_greater_equal(ab, aa), b, tag(eve::min)(a, b)));
        }
      }
      else
      {
        static_assert(wrong<T, U>, "[eve::minmag] - no support for current simd api");
        return a;
      }
    }
    else // if constexpr( is_Vectorized_v<T> || is_Vectorized_v<U> )
    {
      return tag(eve::minmag)(abi_cast<U>(a), abi_cast<T>(b));
    }
  }
}

#endif

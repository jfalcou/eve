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
#include <eve/function/if_else.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/max.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/eps.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE auto ulpdist_(EVE_SUPPORTS(cpu_)
                               , T const &a0
                               , U const &a1) noexcept
  requires(
      std::conditional_t<is_vectorized_v<T>, T, U>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    { return map(eve::ulpdist, abi_cast<value_type_t<U>>(a0), abi_cast<value_type_t<T>>(a1)); }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::ulpdist, abi_cast<value_type_t<U>>(a0), abi_cast<value_type_t<T>>(a1));
    }
    else if constexpr(is_vectorized_v<T> && is_vectorized_v<U>)
    {
      if constexpr(std::is_floating_point_v<value_type_t<T>>)
      {
        using i_t = as_integer_t<T>;
        auto [m1, e1] = pedantic_(ifrexp)(a0);
        auto [m2, e2] = pedantic_(ifrexp)(a1);
        i_t expo =-eve::max(e1, e2);
        T e = if_else( eve::is_equal(e1, e2)
                     , eve::abs(m1-m2)
                     , eve::abs( eve::pedantic_(ldexp)(a0, expo)
                                 - eve::pedantic_(ldexp)(a1, expo))
                     );
        return if_else(numeric_(is_equal)(a0, a1), eve::zero_,e/Eps<T>());
      }
      else
      {
        return dist(a0, a1); 
      }
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::ulpdist(abi_cast<U>(a0), abi_cast<T>(a1));
    }
  }
}

#endif

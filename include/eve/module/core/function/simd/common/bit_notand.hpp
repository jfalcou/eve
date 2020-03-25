//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOTAND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOTAND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  bit_notand_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>, T, U>,
            Bit_compatible<T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    using vt_t  = value_type_t<T>;
    using vu_t  = value_type_t<U>;

    if constexpr(is_Vectorizable_v<T> && !is_Vectorizable_v<U>)
    {
      if constexpr(sizeof(T) == sizeof(vu_t))
        // this will ensure that no scalar conversion will take place in aggregated
        // in the case vector and scalar not of the value type
      {
        return eve::bit_notand(U(bit_cast(a,as_<vu_t>())), b);
      }
      else return U();
    }
    else if constexpr(is_Vectorizable_v<U> && !is_Vectorizable_v<T>)
    {
      if constexpr(sizeof(U) == sizeof(vt_t))
        // this will ensure that no scalar conversion will take place in aggregated
        // in the case vector and scalar not of the value type
      {
        return eve::bit_notand(a, T(bit_cast(b,as_<vt_t>())));
      }
      else return T();
    }
    else if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(bit_notand, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(bit_notand, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_Vectorized_v<T> && is_Vectorized_v<U>)
    {
      return eve::bit_notand(a, bit_cast(b,as(a)));
    }
    else
    {
      static_assert(wrong<T, U>, "[eve::bit_notand] - Missing implementation");
      return T();
    }
  }
}

#endif

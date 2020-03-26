//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_ORNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_ORNOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires bit_compatible<T,U> && (vectorized<T> || vectorized<U>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    using vt_t  = value_type_t<T>;
    using vu_t  = value_type_t<U>;


    if constexpr(vectorizable<T> && !vectorizable<U>)
    {
      if constexpr(sizeof(T) == sizeof(vu_t))
      // this will ensure that no scalar conversion will take place in aggregated
      // in the case vector and scalar not of the value type
      {
        return bit_ornot(U(bit_cast(a,as_<vu_t>())), b);
      }
      else
      {
        static_assert(wrong<T, U>, "[eve::bit_ornot] - sizes are not compatible !");
        return U();
      }
    }
    else if constexpr(vectorizable<U> && !vectorizable<T>)
    {
      if constexpr(sizeof(U) == sizeof(vt_t))
      // this will ensure that no scalar conversion will take place in aggregated
      // in the case vector and scalar not of the value type
      {
        return eve::bit_ornot(a, T(bit_cast(b,as_<vt_t>())));
      }
      else
      {
        static_assert(wrong<T, U>, "[eve::bit_ornot] - sizes are not compatible !");
        return T();
      }
    }
    else if constexpr(emulated<t_abi> || emulated<u_abi>)
    {
      return map(bit_ornot, abi_cast<vu_t>(a), abi_cast<vt_t>(b));
    }
    else if constexpr(aggregated<t_abi> || aggregated<u_abi>)
    {
      return aggregate(bit_ornot, abi_cast<vu_t>(a), abi_cast<vt_t>(b));
    }
    else if constexpr(vectorized<T> && vectorized<U>)
    {
      return eve::bit_or(a, bit_not(bit_cast(b,as(a))));
    }
    else
    {
      static_assert(wrong<T, U>, "[eve::bit_ornot] - Missing implementation");
      return T();
    }
  }
}

#endif

//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/cardinal.hpp>
#include <eve/forward.hpp>
#include <eve/concept/stdconcepts.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  requires bit_compatible<T,U> && (vectorized<T> || vectorized<U>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    using vt_t  = value_type_t<T>;
    using vu_t  = value_type_t<U>;

    if constexpr(vectorizable<T> && !vectorizable<U>)
    {
      return eve::bit_and(U(bit_cast(a,as<vu_t>())), b);
    }
    else if constexpr(vectorizable<U> && !vectorizable<T>)
    {
      return eve::bit_and(a, T(bit_cast(b,as<vt_t>())));
    }
    else if constexpr(emulated<t_abi> || emulated<u_abi>)
    {
      return map(eve::bit_and, abi_cast<value_type_t<U>>(a), abi_cast<vt_t>(b));
    }
    else if constexpr(aggregated<t_abi> || aggregated<u_abi>)
    {
      return aggregate(eve::bit_and, abi_cast<value_type_t<U>>(a), abi_cast<vt_t>(b));
    }
    else
    {
      return eve::bit_and(a, bit_cast(b,as(a)));
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator&(T const &v0, U const &v1) noexcept
      -> decltype(eve::bit_and(v0, v1))
  {
    return eve::bit_and(v0, v1);
  }
}

#endif

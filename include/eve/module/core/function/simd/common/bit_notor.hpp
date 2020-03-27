//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOTOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_NOTOR_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_or.hpp>
#include <type_traits>
#include <eve/detail/has_abi.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto bit_notor_(EVE_SUPPORTS(cpu_)
                                 , T const &a
                                 , U const &b) noexcept
  requires bit_compatible<T,U> && (vectorized<T> || vectorized<U>)
  {
    using vt_t  = value_type_t<T>;
    using vu_t  = value_type_t<U>;

    if constexpr(vectorizable<T> && !vectorizable<U>)
    {
      if constexpr(sizeof(T) == sizeof(vu_t))
        // this will ensure that no scalar conversion will take place in aggregated
        // in the case vector and scalar not of the value type
      {
        return eve::bit_notor(U(bit_cast(a,as_<vu_t>())), b);
      }
      else return U();
    }
    else if constexpr(vectorizable<U> && !vectorizable<T>)
    {
      if constexpr(sizeof(U) == sizeof(vt_t))
      // this will ensure that no scalar conversion will take place in aggregated
      // in the case vector and scalar not of the value type
      {
        return eve::bit_notor(a, T(bit_cast(b,as_<vt_t>())));
      }
      else return T();
    }
    else if constexpr(has_emulated_abi_v<T> || has_emulated_abi_v<U>)
    {
      return map(bit_notor, abi_cast<vu_t>(a), abi_cast<vt_t>(b));
    }
    else if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)
    {
      return aggregate(bit_notor, abi_cast<vu_t>(a), abi_cast<vt_t>(b));
    }
    else if constexpr(vectorized<T> && vectorized<U>)
    {
      return eve::bit_or(bit_not(a), bit_cast(b,as(a)));
    }
    else
    {
      static_assert(wrong<T, U>, "[eve::bit_notor] - Missing implementation");
      return T();
    }
  }
}

#endif

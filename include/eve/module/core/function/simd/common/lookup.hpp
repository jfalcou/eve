//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED
#define EVE__MODULE_CORE_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta/concept.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_mask.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N, typename X, typename Y>
  EVE_FORCEINLINE auto lookup_(EVE_SUPPORTS(cpu_)
                              , wide<T,N,X> const &a, wide<I,N,Y> const &idx) noexcept
  Requires( wide<T,N,X>, behave_as<integral,I> )
  {
    using type = wide<T,N,X>;

    if constexpr( std::is_signed_v<I> )
    {
      return  apply<N::value>([&](auto... v) { return type{a[ idx[v]<0 ? 0 : idx[v]]...}; })
            & bit_mask(idx>=0);
    }
    else
    {
      return  apply<N::value>([&](auto... v) { return type{a[idx[v]<N::value ? idx[v] : 0]...}; })
            & bit_mask(idx<N::value);
    }
  }
}

#endif

//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<scalar_value T, integral_scalar_value I, typename N, typename X, typename Y>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N, X> const &a, wide<I, N, Y> const &ind) noexcept
  {
    using type = wide<T, N, X>;

    if constexpr( std::is_signed_v<I> )
    {
      auto cond = ind >= 0;
      return apply<N::value>([&](auto... v) {
               auto idx = cond.bits();
               idx &= ind;
               return type(a[idx[v]]...);
             })
             & cond.mask();
    }
    else
    {
      auto cond = ind < N::value;
      return apply<N::value>([&](auto... v) {
               auto idx = cond.bits();
               idx &= ind;
               return type(a[idx[v]]...);
             })
             & cond.mask();
    }
  }
}

#endif

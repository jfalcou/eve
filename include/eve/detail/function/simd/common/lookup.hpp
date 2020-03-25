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

#include <eve/detail/overload.hpp>
#include <eve/detail/meta/concept.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/zero.hpp>

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
      return  apply<N::value> ( [&](auto... v)
                                {
                                  auto idx = if_else(ind>=0,ind,eve::zero_);
                                  return type(a[ idx[v] ]...);
                                }
                              )
            & bit_mask(ind>=0);
    }
    else
    {
      return  apply<N::value> ( [&](auto... v)
                                {
                                  auto idx = if_else(ind<N::value,ind,eve::zero_);
                                  return type(a[ idx[v] ]...);
                                }
                              )
             &  bit_mask(ind<N::value);
    }
  }
}

#endif

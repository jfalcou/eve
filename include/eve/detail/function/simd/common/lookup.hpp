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

namespace eve::detail
{
  template<typename T, typename I, typename N, typename X, typename Y>
  EVE_FORCEINLINE auto lookup_(EVE_SUPPORTS(cpu_)
                              , wide<T,N,X> const &a, wide<I,N,Y> const &ind) noexcept
  Requires( wide<T,N,X>, behave_as<integral,I> )
  {
    using type = wide<T,N,X>;

    auto lkup = [](auto const& c, auto const& i, auto const& w)
                {
                  return  apply<N::value> ( [&](auto... v)
                                            {
                                              auto idx = c.bits();
                                              idx &= i;
                                              return type(w[ idx[v] ]...);
                                            }
                                          )
                        & c.mask();
                };

    if constexpr( std::is_signed_v<I> ) return  lkup(ind>=0       , ind , a);
    else                                return  lkup(ind<N::value , ind , a);
  }
}

#endif

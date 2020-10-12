//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/patterns/any_pattern.hpp>
#include <eve/detail/function/patterns/broadcast.hpp>
#include <eve/detail/function/patterns/identity.hpp>
#include <eve/detail/function/patterns/matcher.hpp>
#include <eve/detail/function/patterns/zeroing.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unary swizzle - logical
  //================================================================================================
  template<typename T, typename N, typename ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( cpu_ const&
                              , logical<wide<T,N,ABI>> const& v, Pattern p
                              ) noexcept
  {
    constexpr auto sz = Pattern::size(N::value);
    return bit_cast( v.mask()[p], as<logical<wide<T,fixed<sz>>>>() );
  }

  //================================================================================================
  // Binary swizzle - logical
  //================================================================================================
  template<typename T, typename N, typename ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto shuffle_( cpu_ const&
                              , logical<wide<T,N,ABI>> const& v
                              , logical<wide<T,N,ABI>> const& w
                              , Pattern p
                              ) noexcept
  {
    constexpr auto sz = Pattern::size(N::value);
    return bit_cast( shuffle(v.mask(),w.mask(),p), as<logical<wide<T,fixed<sz>>>>() );
  }

  //================================================================================================
  // Unary swizzle - arithmetic
  //================================================================================================
  template<typename T, typename N, typename ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( cpu_ const&, wide<T,N,ABI> const& r, Pattern p ) noexcept
  {
    swizzle_matcher<zero_match,identity_match,broadcast_match,any_match> that;
    return that(p, r);
  }
}

//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/reduce.hpp>
#include <eve/function/min.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE T minimum_( EVE_SUPPORTS(sse2_)
                            , wide<T,N,ABI> const &v
                            ) noexcept
  {
    constexpr auto c = categorize<wide<T,N,ABI>>();

    if constexpr ( eve::current_api >= eve::sse4_1 )
    {
      if constexpr( c == category::uint16x8 )
      {
        // minupos return a vector like [0 0 0 0 0 0 p m] where m is the minimum and p its position
        // We extract only the minimum.
        return wide<T,N,ABI>(_mm_minpos_epu16(v)).get(0);
      }
      else if constexpr ( c == category::int16x8 )
      {
        auto usv = eve::bit_cast(v, as_<wide<std::uint16_t,N,ABI>>{});
        usv += 32768;
        return static_cast<T>(minimum(usv)-32768);
      }
      else if constexpr( c == category::uint8x16 || c == category::int8x16 )
      {
        // This is less costly than doing the shuffle dance for int8s
        auto [lw,hw] = convert(v, as_<std::uint16_t>{}).slice();
        return static_cast<T>(minimum( min(lw,hw) ));
      }
      else
      {
        return reduce(v, eve::min);
      }
    }
    else
    {
      return reduce(v, eve::min);
    }
  }

  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(sse2_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
    if constexpr ( eve::current_api >= eve::sse4_1 && sizeof(T) <= 2 )
    {
      return wide<T,N,ABI>(minimum(v));
    }
    else
    {
      return splat(reduce)(v, eve::min);
    }
  }
}

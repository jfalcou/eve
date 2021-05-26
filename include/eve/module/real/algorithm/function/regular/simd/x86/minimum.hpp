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
#include <eve/detail/function/reduce.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/replace.hpp>
#include <eve/function/min.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  requires(sizeof(T) <= 2)
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(sse4_1_)
                                , wide<T,N,ABI> v
                                ) noexcept
  {
    constexpr auto c = categorize<wide<T,N,ABI>>();

    if constexpr( N::value == 1 )
    {
      return v.get(0);
    }
    else if constexpr( !std::same_as<abi_t<T, N>,x86_128_> )
    {
      // Larger X86 ABI slices and try to optimize down the road
      auto [lw,hw] = v.slice();
      return static_cast<T>(minimum( min(lw,hw) ));
    }
    else
    {
      if constexpr( c == category::uint16x8 )
      {
        constexpr auto fix = [](auto w)
        {
          if constexpr(N::value < 8)  return replace_ignored( wide<T,fixed<8>>(w.storage())
                                                            , ignore_last(8-N::value)
                                                            , T(~0)
                                                            );
          else                        return w;
        };

        // minupos return a vector like [0 0 0 0 0 0 p m] where m is the minimum and p its position
        // We extract only the minimum.
        using type = wide<T,N,ABI>;
        return type(_mm_minpos_epu16(fix(v))).get(0);
      }
      else if constexpr ( c == category::int16x8 )
      {
        auto usv = eve::bit_cast(v, as_<wide<std::uint16_t,N,ABI>>{});
        auto const sm = signmask(as_<T>());
        usv += sm;
        return static_cast<T>(minimum(usv)-sm);
      }
      else if constexpr( c == category::uint8x16 )
      {
        // This is less costly than doing the shuffle dance for int8s
        auto [lw,hw] = convert(v, as_<std::uint16_t>{}).slice();
        return static_cast<T>(minimum( min(lw,hw) ));
      }
      else if constexpr( c == category::int8x16 )
      {
        // This is less costly than doing the shuffle dance for int8s
        auto [lw,hw] = convert(v, as_<std::int16_t>{}).slice();
        return static_cast<T>(minimum( min(lw,hw) ));
      }
    }
  }

  template<real_scalar_value T, typename N, x86_abi ABI>
  requires(sizeof(T) <= 2)
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(sse4_1_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
    return wide<T,N,ABI>(minimum(v));
  }
}

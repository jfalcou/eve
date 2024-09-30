//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/fms.hpp>

#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fnms_(EVE_REQUIRES(sse2_),
                                   O const& opts,
                                   wide<T, N> const& a,
                                   wide<T, N> const& b,
                                   wide<T, N> const& c) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();
    // Integral don't do anything special ----
    if constexpr( std::integral<T> ) return fnms.behavior(cpu_{}, opts, a, b, c);
    // UPPER LOWER  ----
    else if constexpr(O::contains(lower) || O::contains(upper))
    {
      if(!O::contains(strict))
      {
        if constexpr(current_api >= avx512)
        {
          auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
          if      constexpr  ( cat == category::float64x8  ) return  _mm512_fnmsub_round_pd (a, b, c, dir);
          else if constexpr  ( cat == category::float32x16 ) return  _mm512_fnmsub_round_ps (a, b, c, dir);
          else if constexpr  ( cat == category::float64x4 ||  cat == category::float64x2 ||
                               cat == category::float32x8 ||  cat == category::float32x4 || cat == category::float32x2)
          {
            auto aa = eve::combine(a, a);
            auto bb = eve::combine(b, b);
            auto cc = eve::combine(c, c);
            auto aabbcc = fnms[opts](aa, bb, cc);
            return  slice(aabbcc, eve::upper_);
          }
          else                                             return fnms.behavior(cpu_{}, opts, a, b, c);
        }
        else                                               return fnms.behavior(cpu_{}, opts, a, b, c);
      }
      else                                                 return fnms.behavior(cpu_{}, opts, a, b, c);
    }    // PEDANTIC ---
    else if constexpr(O::contains(pedantic) )
    {
      if constexpr( supports_fma3 ) return fnms(a, b, c);
      else                          return fnms.behavior(cpu_{}, opts, a, b, c);
    }
    // REGULAR ---
    // we don't care about PROMOTE as we only accept similar types.
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr( cat == category::float64x8  )  return _mm512_fnmsub_pd(a, b, c);
      else if constexpr( cat == category::float32x16 )  return _mm512_fnmsub_ps(a, b, c);
      else if constexpr( supports_fma3)
      {
        if      constexpr( cat == category::float64x4 ) return _mm256_fnmsub_pd(a, b, c);
        else if constexpr( cat == category::float64x2 ) return _mm_fnmsub_pd   (a, b, c);
        else if constexpr( cat == category::float32x8 ) return _mm256_fnmsub_ps(a, b, c);
        else if constexpr( cat == category::float32x4 ) return _mm_fnmsub_ps   (a, b, c);
      }
      else return fnms.behavior(cpu_{}, opts, a, b, c);
    }
  }


  template<typename T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N> fnms_( EVE_REQUIRES(avx512_),
                                    C const& mask,
                                    O const&opts
                                  , wide<T, N> const& a,
                                    wide<T, N> const& b,
                                    wide<T, N> const& c
      )
  noexcept requires x86_abi<abi_t<T, N>>
  {
    // NOTE: As those masked version are at the AVX512 level, they will always uses a variant of
    // hardware VMADD, thus ensuring the pedantic behavior by default, hence why we don't care about
    // PEDANTIC. As usual, we don't care about PROMOTE as we only accept similar types.

    if      constexpr( C::is_complete )               return alternative(mask, a, as(a));
    else if constexpr( !C::has_alternative )
    {
      constexpr auto              cx = categorize<wide<T, N>>();
      auto src = alternative(mask, a, as<wide<T, N>> {});
      [[maybe_unused]] auto const m  = expand_mask(mask, as(a)).storage().value;

      // Integral don't do anything special ----
      if constexpr( std::integral<T> ) return fnms.behavior(cpu_{}, opts, a, b, c);
      // UPPER LOWER  ----
      else if constexpr(O::contains(lower) || O::contains(upper))
      {
        if constexpr(!O::contains(strict))
        {
          if constexpr(current_api >= avx512)
          {
            auto constexpr dir =(O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) |_MM_FROUND_NO_EXC;
            if      constexpr  ( c == category::float64x8  ) return  _mm512_mask_fnmsub_round_pd (a, m, b, c, dir);
            else if constexpr  ( c == category::float32x16 ) return  _mm512_mask_fnmsub_round_ps (a, m, b, c, dir);
            else if constexpr  ( c == category::float64x4 ||  c == category::float64x2 ||
                                 c == category::float32x8 ||  c == category::float32x4 || c == category::float32x2)
            {
              auto aa = eve::combine(a, a);
              auto bb = eve::combine(b, b);
              auto cc = eve::combine(c, c);
              auto aabbcc = fma[opts.drop(condition_key)](aa, bb, cc);
              auto s =  slice(aabbcc, eve::upper_);
              return if_else(cx,s,src);
            }
            else                                             return fnms.behavior(cpu_{}, opts, a, b, c);
          }
          else                                               return fnms.behavior(cpu_{}, opts, a, b, c);
        }
        else                                                 return fnms.behavior(cpu_{}, opts, a, b, c);
      }
      if      constexpr( cx == category::float32x16 ) return _mm512_mask_fnmsub_ps(a, m, b, c);
      else if constexpr( cx == category::float64x8  ) return _mm512_mask_fnmsub_pd(a, m, b, c);
      else if constexpr( cx == category::float32x8  ) return _mm256_mask_fnmsub_ps(a, m, b, c);
      else if constexpr( cx == category::float64x4  ) return _mm256_mask_fnmsub_pd(a, m, b, c);
      else if constexpr( cx == category::float32x4  ) return _mm_mask_fnmsub_ps   (a, m, b, c);
      else if constexpr( cx == category::float64x2  ) return _mm_mask_fnmsub_pd   (a, m, b, c);
      // No rounding issue with integers, so we just mask over regular FMA
      else                                            return if_else(mask, eve::fnms(a, b, c), a);
    }
    else                                              return if_else(mask, eve::fnms(a, b, c), alternative(mask, a, as(a)));
  }
}

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
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto exponent_(EVE_REQUIRES(avx512_), O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if  constexpr(O::contains(raw))
    {
      using r_t    = wide<T, N>;
      constexpr auto c = categorize<r_t>();
      if      constexpr( c == category::float64x8 ) return convert(r_t(_mm512_getexp_pd(w)), int_from<T>());
      else if constexpr( c == category::float32x16) return convert(r_t(_mm512_getexp_ps(w)), int_from<T>());
      else if constexpr( c == category::float64x4 ) return convert(r_t(_mm256_getexp_pd(w)), int_from<T>());
      else if constexpr( c == category::float32x8 ) return convert(r_t(_mm256_getexp_ps(w)), int_from<T>());
      else if constexpr( c == category::float64x2 ) return convert(r_t(_mm_getexp_pd(w)), int_from<T>());
      else if constexpr( c == category::float32x4 ) return convert(r_t(_mm_getexp_ps(w)), int_from<T>());
    }
    else
      return exponent.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto exponent_(EVE_REQUIRES(avx512_), C const& mask, O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    auto const            s = alternative(mask, w, as{w});
    [[maybe_unused]] auto m = expand_mask(mask, as{w}).storage().value;
    constexpr auto        c = categorize<wide<T, N>>();

    if constexpr( C::is_complete ) return s;
    else if  constexpr(O::contains(raw))
    {
      using r_t        = wide<T, N>;

      auto compute = [](auto w, auto cx){
        auto src = alternative(cx, w, as<wide<T, N>> {});
        auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

        if      constexpr( c == category::float32x16) return convert(r_t(_mm512_mask_getexp_ps(src, m, w)), int_from<T>());
        else if constexpr( c == category::float64x8 ) return convert(r_t(_mm512_mask_getexp_pd(src, m, w)), int_from<T>());
        else if constexpr( c == category::float64x4 ) return convert(r_t(_mm256_mask_getexp_pd(src, m, w)), int_from<T>());
        else if constexpr( c == category::float32x8 ) return convert(r_t(_mm256_mask_getexp_ps(src, m, w)), int_from<T>());
        else if constexpr( c == category::float64x2 ) return convert(r_t(_mm_mask_getexp_pd(src, m, w)), int_from<T>());
        else if constexpr( c == category::float32x4 ) return convert(r_t(_mm_mask_getexp_ps(src, m, w)), int_from<T>());
      };
    }
    else return exponent.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
  }
}

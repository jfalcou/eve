//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
  EVE_FORCEINLINE auto exponent_(EVE_SUPPORTS(avx512_), wide<T, N> a0) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    using r_t = wide<T, N>;
    auto compute = [](auto a0){
      constexpr auto c = categorize<r_t>();
      if constexpr ( c == category::float64x8  ) return int_(r_t(_mm512_getexp_pd(a0)));
      else if constexpr ( c == category::float32x16 ) return int_(r_t(_mm512_getexp_ps(a0)));
      else if constexpr ( c == category::float64x4  ) return int_(r_t(_mm256_getexp_pd(a0)));
      else if constexpr ( c == category::float32x8  ) return int_(r_t(_mm256_getexp_ps(a0)));
      else if constexpr ( c == category::float64x2  ) return int_(r_t(_mm_getexp_pd(a0)));
      else if constexpr ( c == category::float32x4  ) return int_(r_t(_mm_getexp_ps(a0)));
    };
    return if_else(is_eqz(a0),  zero, compute(a0));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto exponent_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    using r_t = wide<T, N>;
    constexpr auto c = categorize<r_t>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return exponent_(EVE_RETARGET(cpu_),cx,v);
    }
    else
    {
      auto compute = [](auto v, auto cx){
        auto src  = alternative(cx,v,as<wide<T, N>>{});
        auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

        if constexpr ( c == category::float32x16 ) return int_(r_t(_mm512_mask_getexp_ps(src,m,v)));
        else if constexpr ( c == category::float64x8  ) return int_(r_t(_mm512_mask_getexp_pd(src,m,v)));
        else if constexpr ( c == category::float64x4  ) return int_(r_t(_mm256_mask_getexp_pd(src,m,v)));
        else if constexpr ( c == category::float32x8  ) return int_(r_t(_mm256_mask_getexp_ps(src,m,v)));
        else if constexpr ( c == category::float64x2  ) return int_(r_t(_mm_mask_getexp_pd(src,m,v)));
        else if constexpr ( c == category::float32x4  ) return int_(r_t(_mm_mask_getexp_ps(src,m,v)));
      };
      return if_else(is_eqz(v),  zero, compute(v, cx));
    }
  }
}

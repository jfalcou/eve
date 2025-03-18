//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/detail/flags.hpp>

namespace eve::detail
{

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_eqz_(EVE_REQUIRES(avx512_),
                                                   O          const &,
                                                   wide<T, N> const &a) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto f = (eve::poszero | eve::negzero).value;

    using s_t = typename l_t::storage_type;

         if constexpr( c == category::float64x8 ) return s_t {_mm512_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x4 ) return s_t {_mm256_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float64x2 ) return s_t {_mm_fpclass_pd_mask(a, f)};
    else if constexpr( c == category::float32x16) return s_t {_mm512_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x8 ) return s_t {_mm256_fpclass_ps_mask(a, f)};
    else if constexpr( c == category::float32x4 ) return s_t {_mm_fpclass_ps_mask(a, f)};
  }


// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto is_eqz_(EVE_REQUIRES(avx512_),
                                     C const& cx,
                                     O const& o,
                                     wide<T, N> const& v) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return is_eqz[o][cx].retarget(cpu_{}, v);
    }
    else
    {
      auto           m = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      constexpr auto f = (eve::poszero | eve::negzero).value;

      if constexpr( c == category::float32x16 )     return mask16 {_mm512_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x8 ) return mask8 {_mm512_mask_fpclass_pd_mask(m, v, f)};
      else if constexpr( c == category::float32x8 ) return mask8 {_mm256_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x4 ) return mask8 {_mm256_mask_fpclass_pd_mask(m, v, f)};
      else if constexpr( c == category::float32x4 ) return mask8 {_mm_mask_fpclass_ps_mask(m, v, f)};
      else if constexpr( c == category::float64x2 ) return mask8 {_mm_mask_fpclass_pd_mask(m, v, f)};
    }
  }
}

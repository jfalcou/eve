//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/true.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_ordered_( EVE_SUPPORTS(sse2_), wide<T,N> const& a, wide<T,N> const& b) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    using l_t = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T,N>>();
    constexpr auto m = _CMP_ORD_Q;

          if constexpr( c && category::integer_    )  return true_(eve::as<l_t>());
    else  if constexpr( current_api >= eve::avx512 )
    {
      using s_t = typename l_t::storage_type;

            if constexpr(c == category::float64x8  ) return s_t{_mm512_cmp_pd_mask(a, b, m) };
      else  if constexpr(c == category::float64x4  ) return s_t{_mm256_cmp_pd_mask(a, b, m) };
      else  if constexpr(c == category::float64x2  ) return s_t{_mm_cmp_pd_mask   (a, b, m) };
      else  if constexpr(c == category::float32x16 ) return s_t{_mm512_cmp_ps_mask(a, b, m) };
      else  if constexpr(c == category::float32x8  ) return s_t{_mm256_cmp_ps_mask(a, b, m) };
      else  if constexpr(c == category::float32x4  ) return s_t{_mm_cmp_ps_mask   (a, b, m) };
    }
    else  if constexpr(c == category::float64x4  ) return l_t(_mm256_cmp_pd   (a, b, m) );
    else  if constexpr(c == category::float64x2  ) return l_t(_mm_cmpord_pd (a, b)    );
    else  if constexpr(c == category::float32x8  ) return l_t(_mm256_cmp_ps   (a, b, m) );
    else  if constexpr(c == category::float32x4  ) return l_t(_mm_cmpord_ps (a, b)    );
  }
}

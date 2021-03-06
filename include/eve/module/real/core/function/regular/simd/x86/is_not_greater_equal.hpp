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

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE logical<wide<T, N, ABI>>
  is_not_greater_equal_ ( EVE_SUPPORTS(sse2_)
                        , wide<T,N,ABI> const& a, wide<T,N,ABI> const& b
                        ) noexcept
  {
    using s_t = typename logical<wide<T, N, ABI>>::storage_type;
    constexpr auto c = categorize<wide<T,N,ABI>>();

    if constexpr( !x86_128_::is_wide_logical )
    {
      return is_not_greater_equal_(EVE_RETARGET(cpu_), a, b);
    }
    else if constexpr(c == category::float64x8  ) return s_t( _mm512_cmp_pd(a, b, _CMP_NGE_UQ));
    else if constexpr(c == category::float64x4  ) return s_t( _mm256_cmp_pd(a, b, _CMP_NGE_UQ));
    else if constexpr(c == category::float64x2  ) return s_t( _mm_cmpnge_pd(a, b)             );
    else if constexpr(c == category::float32x16 ) return s_t( _mm512_cmp_ps(a, b, _CMP_NGE_UQ));
    else if constexpr(c == category::float32x8  ) return s_t( _mm256_cmp_ps(a, b, _CMP_NGE_UQ));
    else if constexpr(c == category::float32x4  ) return s_t( _mm_cmpnge_ps(a, b)             );
  }
}

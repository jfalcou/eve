//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/if_else.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/count_true.hpp>

namespace eve::detail
{

  template <typename U, typename N>
  struct do_compress_bmi
  {
    logical<wide<U, N>> mask;

    template <kumi::product_type T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      return { kumi::map (*this, v) };
    }

    template <typename T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto m = mask.storage().value;

           if constexpr ( match(c, category::float32x4                     ) ) return _mm_maskz_compress_ps      (m, v);
      else if constexpr ( match(c, category::float32x8                     ) ) return _mm256_maskz_compress_ps   (m, v);
      else if constexpr ( match(c, category::int32x4  , category::uint32x4 ) ) return _mm_maskz_compress_epi32   (m, v);
      else if constexpr ( match(c, category::int32x8  , category::uint32x8 ) ) return _mm256_maskz_compress_epi32(m, v);
      else if constexpr ( match(c, category::float64x2                     ) ) return _mm_maskz_compress_pd      (m, v);
      else if constexpr ( match(c, category::float64x4                     ) ) return _mm256_maskz_compress_pd   (m, v);
      else if constexpr ( match(c, category::int64x2  , category::uint64x2 ) ) return _mm_maskz_compress_epi64   (m, v);
      else if constexpr ( match(c, category::int64x4  , category::uint64x4 ) ) return _mm256_maskz_compress_epi64(m, v);
    }
  };

  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_using_bmi_(EVE_SUPPORTS(avx512_),
                           C c,
                           wide<T, N> v,
                           logical<wide<U, N>> mask) noexcept
    requires (min_scalar_size_v<T> >= 4)
  {
    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( !C::is_complete )
    {
      mask = mask && c.mask(as(mask));
      return compress_using_bmi(ignore_none, v, mask);
    }
    else if constexpr ( N() == 1 )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) mask.get(0) };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( N() == 2 )
    {
      auto to_left     = eve::slide_left( v, eve::index<1> );
      auto compressed  = eve::if_else[mask]( v, to_left );

      kumi::tuple cur{ compressed, eve::count_true(mask) };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( max_scalar_size_v<T> * N() > 32 )
    {
      auto [l, h] = v.slice();
      auto [ml, mh] = mask.slice();

      auto lr = compress_using_bmi(ignore_none, l, ml);
      auto hr = compress_using_bmi(ignore_none, h, mh);

      return kumi::cat(lr, hr);
    }
    else
    {
      v = do_compress_bmi<U, N>{mask}(v);
      kumi::tuple cur {v, eve::count_true(mask)};
      return kumi::tuple<decltype(cur)>{ cur };
    }
  }
}

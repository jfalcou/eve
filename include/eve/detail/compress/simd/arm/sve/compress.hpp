//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/count_true.hpp>

namespace eve::detail
{
  template <typename U, typename N>
  struct do_compress_sve
  {
    eve::logical<eve::wide<U, N>> mask;

    template <kumi::product_type T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      return { kumi::map (*this, v) };
    }

    template <typename T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
      requires ( sizeof(T) < 4 )
    {
      auto bigger = operator()(eve::convert(v, eve::as<std::int32_t>{}));
      return eve::convert(bigger, eve::as<T>{});
    }

    template <typename T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      return svcompact(convert(mask, as<logical<T>>{}), v);
    }
  };

  template<typename T, typename N> constexpr bool compress_sve_should_split()
  {
    std::size_t min_size = kumi::min_flat( T{}, [](auto m) { return sizeof(m); });
    std::size_t max_size = kumi::max_flat( T{}, [](auto m) { return sizeof(m); });

    // We can compress 1 full register of at least 4 bytes elements.
    if (min_size == 1U                  ) return N() > eve::expected_cardinal_v<std::int32_t> / 4;
    if (min_size == 2U || max_size == 8U) return N() > eve::expected_cardinal_v<std::int32_t> / 2;
    return N() > eve::expected_cardinal_v<std::int32_t>;
  }

  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_(EVE_SUPPORTS(sve_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
  {
    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( !C::is_complete )
    {
      return compress(ignore_none, v, mask && c.mask(as(mask)));
    }
    else if constexpr ( compress_sve_should_split<T, N>() )
    {
      auto [lo, hi]   = v.slice();
      auto [mlo, mhi] = mask.slice();
      return kumi::cat(compress(ignore_none, lo, mlo), compress(ignore_none, hi, mhi));
    }
    else
    {
      v = do_compress_sve<U, N>{mask}(v);
      kumi::tuple cur {v, count_true(mask)};
      return kumi::tuple<decltype(cur)>{ cur };
    }
  }
}

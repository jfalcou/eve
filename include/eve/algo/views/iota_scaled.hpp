//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/views/convert.hpp>

#include <eve/function/read.hpp>
#include <eve/function/load.hpp>
#include <eve/function/replace.hpp>

namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!
  //! @}

  template <typename T, typename N>
  struct iota_scaled_iterator : operations_with_distance
  {
    using value_type = T;
    using wv_type    = eve::wide<value_type, N>;

    std::ptrdiff_t  i;
    value_type      scale;
    wv_type         wide_cur;

    iota_scaled_iterator() = default;

    EVE_FORCEINLINE iota_scaled_iterator(std::ptrdiff_t i_, value_type scale) :
      i(0), scale(scale)
    {
      wide_cur = wv_type {[&](int j, int) { return j; }};
      wide_cur *= scale;
      *this += i_;
    }

    iota_scaled_iterator unaligned() const { return *this; }
    iota_scaled_iterator previous_partially_aligned() const { return *this; }

    static N iterator_cardinal() { return {}; }

    template <typename _N>
    auto cardinal_cast(_N) const { return iota_scaled_iterator<T, _N>{i, scale}; }

    iota_scaled_iterator& operator+=(std::ptrdiff_t n)
    {
      i += n;
      wide_cur += scale * n;
      return *this;
    }

    friend std::ptrdiff_t operator-(iota_scaled_iterator x, iota_scaled_iterator y)
    {
      EVE_ASSERT(x.scale == y.scale, "different scale");
      return x.i - y.i;
    }

    bool operator== (iota_scaled_iterator const& x) const
    {
      EVE_ASSERT(scale == x.scale, "different scale");
      return i ==  x.i;
    }
    auto operator<=>(iota_scaled_iterator const& x) const
    {
      EVE_ASSERT(scale == x.scale, "different scale");
      return i <=> x.i;
    }

    EVE_FORCEINLINE friend T tagged_dispatch(eve::tag::read_, iota_scaled_iterator self)
    {
      return self.scale * self.i;
    }

    template <typename U>
    EVE_FORCEINLINE friend auto tagged_dispatch(convert_, iota_scaled_iterator self, eve::as<U> tgt)
    {
      return iota_scaled_iterator<U, N>{self.i, eve::convert(self.scale, tgt)};
    }

    template<relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend wv_type tagged_dispatch(eve::tag::load_,
                                                   C const & c,
                                                   S const &,
                                                   eve::as<wv_type> const &,
                                                   iota_scaled_iterator self)
    {
      if constexpr ( !C::has_alternative ) return self.wide_cur;
      else
      {
        return eve::replace_ignored(self.wide_cur, c, c.alternative);
      }
    }
  };

  struct
  {
    template <typename T, typename N>
    EVE_FORCEINLINE auto operator()(std::ptrdiff_t i, T scale, N) const
    {
      return iota_scaled_iterator<T, N>{i, scale};
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(std::ptrdiff_t i, T scale) const
    {
      return operator()(i, scale, eve::lane<eve::expected_cardinal_v<T>>);
    }
  } inline constexpr iota_scaled_unbound;
}

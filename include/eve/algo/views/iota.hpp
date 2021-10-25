//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
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
  //!    @struct base_plus_offset_iterator
  //!    @brief An iterator for all values from base to offset.
  //!    Should be created with `iota_scaled` or `iota`.
  //!    Not OK to compare two iterators generated from a different base.
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::base_plus_offset_iterator` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  template <typename T, typename N>
  struct base_plus_offset_iterator : operations_with_distance
  {
    using value_type = T;
    using wv_type    = eve::wide<value_type, N>;

    value_type      base;
    value_type      scale;
    std::ptrdiff_t  i;
    wv_type         wide_cur;

    base_plus_offset_iterator() = default;

    EVE_FORCEINLINE base_plus_offset_iterator(value_type base,
                                              value_type scale,
                                              std::ptrdiff_t i_) :
      base(base),
      scale(scale),
      i(0)
    {
      wide_cur = wv_type {[&](int j, int) { return j; }};
      wide_cur *= scale;
      wide_cur += base;
      operator+=(i_);
    }

    base_plus_offset_iterator unaligned() const { return *this; }
    base_plus_offset_iterator previous_partially_aligned() const { return *this; }

    static N iterator_cardinal() { return {}; }

    template <typename _N>
    auto cardinal_cast(_N) const { return base_plus_offset_iterator<T, _N>{base, scale, i}; }

    base_plus_offset_iterator& operator+=(std::ptrdiff_t n)
    {
      i += n;
      wide_cur += scale * n;
      return *this;
    }

    friend std::ptrdiff_t operator-(base_plus_offset_iterator x, base_plus_offset_iterator y)
    {
      EVE_ASSERT(x.base == y.base,   "different base");
      EVE_ASSERT(x.scale == y.scale, "different scale");
      return x.i - y.i;
    }

    bool operator== (base_plus_offset_iterator const& x) const
    {
      EVE_ASSERT(base  == x.base,   "different base");
      EVE_ASSERT(scale == x.scale, "different scale");
      return i ==  x.i;
    }
    auto operator<=>(base_plus_offset_iterator const& x) const
    {
      EVE_ASSERT(base  == x.base,   "different base");
      EVE_ASSERT(scale == x.scale, "different scale");
      return i <=> x.i;
    }

    EVE_FORCEINLINE friend T tagged_dispatch(eve::tag::read_, base_plus_offset_iterator self)
    {
      return self.base + eve::convert(self.i * self.scale, eve::as<T>{});
    }

    template <typename U>
    EVE_FORCEINLINE friend auto tagged_dispatch(convert_, base_plus_offset_iterator self, eve::as<U> tgt)
    {
      return base_plus_offset_iterator<U, N>{
        eve::convert(self.base, tgt),
        eve::convert(self.scale, tgt),
        self.i
      };
    }

    template<relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend wv_type tagged_dispatch(eve::tag::load_,
                                                   C const & c,
                                                   S const &,
                                                   eve::as<wv_type> const &,
                                                   base_plus_offset_iterator self)
    {
      if constexpr ( !C::has_alternative ) return self.wide_cur;
      else
      {
        return eve::replace_ignored(self.wide_cur, c, c.alternative);
      }
    }
  };

  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!    @var iota_scaled
  //!    @brief A fuction to generate an `iota` scaled by some multiplier.
  //!    To generate an iterator pass T base, T scale.
  //!    For a range pass a range size as ptrdiff_t as a 3rd parameter.
  //!
  //!    Example: iota_scaled(0.1, 0.2, 3) is a range [0.1, 0.3, 0.5]
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::iota_scaled` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  struct
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, T scale) const
    {
      using N = eve::fixed<eve::expected_cardinal_v<T>>;
      return base_plus_offset_iterator<T, N>{base, scale, 0};
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, T scale, std::ptrdiff_t size) const
    {
      auto f = operator()(base, scale);
      auto l = f + size;
      return eve::algo::as_range(f, l);
    }
  } inline constexpr iota_scaled;

  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!    @var iota
  //!    @brief A fuction to generate an `iota` iterator/view like [0, 1, 2, 3, ...].
  //!    To generate an iterator pass T base.
  //!    For a range pass a range size as ptrdiff_t as a 2rd parameter.
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::iota_scaled` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  struct
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T base) const
    {
      return iota_scaled(base, T{1});
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, std::ptrdiff_t size) const
    {
      return iota_scaled(base, T{1}, size);
    }
  } inline constexpr iota;
}

//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/as_range.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/views/convert.hpp>


namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @struct iota_with_step_iterator
  //!    @brief An iterator for all values from base to offset.
  //!    Should be created with `iota_with_step` or `iota`.
  //!    Not OK to compare two iterators generated from a different base.
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::iota_with_step_iterator` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  template <typename T, typename N>
  struct iota_with_step_iterator : operations_with_distance
  {
    using value_type = T;
    using wv_type    = eve::wide<value_type, N>;

    value_type      base;
    value_type      step;
    std::ptrdiff_t  i;
    wv_type         wide_cur;

    iota_with_step_iterator() = default;

    EVE_FORCEINLINE iota_with_step_iterator(value_type base,
                                              value_type step,
                                              std::ptrdiff_t i_) :
      base(base),
      step(step),
      i(0)
    {
      wide_cur = wv_type {[&](int j, int) { return j; }};
      wide_cur *= step;
      wide_cur += base;
      operator+=(i_);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::unalign_, iota_with_step_iterator self )
    {
      return self;
    }

    iota_with_step_iterator previous_partially_aligned() const { return *this; }
    iota_with_step_iterator next_partially_aligned()     const { return *this; }

    static N iterator_cardinal() { return {}; }

    template <typename _N>
    auto cardinal_cast(_N) const { return iota_with_step_iterator<T, _N>{base, step, i}; }

    iota_with_step_iterator& operator+=(std::ptrdiff_t n)
    {
      i += n;
      wide_cur += step * n;
      return *this;
    }

    friend std::ptrdiff_t operator-(iota_with_step_iterator x, iota_with_step_iterator y)
    {
      EVE_ASSERT(x.base == y.base, "different base");
      EVE_ASSERT(x.step == y.step, "different step");
      return x.i - y.i;
    }

    bool operator== (iota_with_step_iterator const& x) const
    {
      EVE_ASSERT(base == x.base, "different base");
      EVE_ASSERT(step == x.step, "different step");
      return i ==  x.i;
    }
    auto operator<=>(iota_with_step_iterator const& x) const
    {
      EVE_ASSERT(base == x.base, "different base");
      EVE_ASSERT(step == x.step, "different step");
      return i <=> x.i;
    }

    EVE_FORCEINLINE friend T tagged_dispatch(eve::tag::read_, iota_with_step_iterator self)
    {
      return self.base + eve::convert(self.i * self.step, eve::as<T>{});
    }

    template <typename U>
    EVE_FORCEINLINE friend auto tagged_dispatch(convert_, iota_with_step_iterator self, eve::as<U> tgt)
    {
      return iota_with_step_iterator<U, N>{
        eve::convert(self.base, tgt),
        eve::convert(self.step, tgt),
        self.i
      };
    }

    template<relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend wv_type tagged_dispatch(eve::tag::load_,
                                                   C const & c,
                                                   S const &,
                                                   eve::as<wv_type> const &,
                                                   iota_with_step_iterator self)
    {
      if constexpr ( !C::has_alternative ) return self.wide_cur;
      else
      {
        return eve::replace_ignored(self.wide_cur, c, c.alternative);
      }
    }
  };

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @var iota_with_step
  //!    @brief A fuction to generate an `iota` with a step i.e. a general arithmetic sequence.
  //!    To generate an iterator pass T base, T step.
  //!    For a range pass a range size as ptrdiff_t as a 3rd parameter.
  //!
  //!    Example: iota_with_step(0.1, 0.2, 4) is a range [0.1, 0.3, 0.5, 0.7]
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::iota_with_step` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  struct
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, T step) const
    {
      using N = eve::fixed<eve::expected_cardinal_v<T>>;
      return iota_with_step_iterator<T, N>{base, step, 0};
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, T step, std::ptrdiff_t size) const
    {
      auto f = operator()(base, step);
      auto l = f + size;
      return eve::algo::as_range(f, l);
    }
  } inline constexpr iota_with_step;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @var iota
  //!    @brief A fuction to generate an `iota` iterator/view like [0.5, 2.5,  4.5, ...]. \f$(0.5 + 2(n-1))_{n \in \N}\f$
  //!    To generate an iterator base + (n-1) step  pass T base and T step.
  //!    For a range pass a range size as ptrdiff_t as a 2rd parameter.
  //!
  //!    **Required header:** `#include <eve/algo/views/iota.hpp>`
  //!
  //!    Has a shorthand `eve::views::iota_with_step` in `<eve/views/iota.hpp>`.
  //! @}
  //================================================================================================

  struct
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T base) const
    {
      return iota_with_step(base, T{1});
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, std::ptrdiff_t size) const
    {
      return iota_with_step(base, T{1}, size);
    }
  } inline constexpr iota;
}

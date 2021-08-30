//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/detail/convert.hpp>

#include <eve/function/convert.hpp>
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

namespace eve::algo
{
  template <typename I, typename T>
  struct converting_iterator : operations_with_distance
  {
    using cardinal = typename I::cardinal;
    using value_type = T;
    using wide_value_type = eve::wide<value_type, cardinal>;

    converting_iterator() = default;
    explicit converting_iterator(I base) : base(base) {}

    operator converting_iterator<unaligned_t<I>, T>() const
      requires (!unaligned_iterator<I>)
    {
      return converting_iterator<unaligned_t<I>, T>{base};
    }

    converting_iterator<unaligned_t<I>, T> unaligned() const { return *this; }
    auto previous_partially_aligned() const
    {
      return converting_iterator<partially_aligned_t<I>, T>{base.previous_partially_aligned()};
    }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal N) const
    {
      auto new_base = base.cardinal_cast(N);
      return converting_iterator<decltype(new_base), T>{new_base};
    }

    T operator*() const { return static_cast<T>(*base); }

    template <sentinel_for<I> I2>
    friend bool operator==(converting_iterator const& x, converting_iterator<I2, T> const& y)
    {
      return x.base == y.base;
    }

    template <sentinel_for<I> I2>
    auto operator<=>(converting_iterator<I2, T> const & x) const
    {
      return base <=> x.base;
    }

    converting_iterator&  operator+=(std::ptrdiff_t n) { base += n; return *this; }

    template <sentinel_for<I> I2>
    std::ptrdiff_t operator-(converting_iterator<I2, T> const & x) const
    {
      return base - x.base;
    }

    template< relative_conditional_expr C, decorator S, typename Pack>
    friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , eve::as<Pack> const& tgt, converting_iterator self
                                )
    {
      auto c1 = map_alternative(
        c,
        [](auto alt) { return eve::convert(alt, eve::as<typename I::value_type>{}); }
      );

      return eve::convert(eve::load(c1, s, tgt, self.base), eve::as<T>{});
    }

    template <relative_conditional_expr C>
    friend void tagged_dispatch(
      eve::tag::store_, C c, wide_value_type v, converting_iterator self )
    {
      auto c1 = map_alternative(
        c,
        [](auto alt) { return eve::convert(alt, eve::as<typename I::value_type>{}); }
      );

      eve::store[c1](eve::convert(v, eve::as<typename I::value_type>{}), self.base);
    }

    friend void tagged_dispatch( eve::tag::store_, wide_value_type v, converting_iterator self )
    {
      eve::store(eve::convert(v, eve::as<typename I::value_type>{}), self.base);
    }

    I base;
  };
}

//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/concepts/eve_iterator.hpp>
#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/detail/convert.hpp>
#include <eve/algo/detail/preprocess_range.hpp>
#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/convert.hpp>
#include <eve/function/read.hpp>
#include <eve/function/write.hpp>
#include <eve/function/compress_store.hpp>
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

namespace eve::algo
{
  template <typename I, typename T>
  struct converting_iterator;

  namespace detail
  {
    template <typename I, typename T>
    struct converting_iterator_common : operations_with_distance
    {
      I base;
      using value_type = T;

      converting_iterator_common() = default;

      EVE_FORCEINLINE explicit converting_iterator_common(I base) : base(base) {}

      EVE_FORCEINLINE auto unaligned() const
      {
        return convert(unalign(base), as<T>{});
      }

      EVE_FORCEINLINE operator converting_iterator<unaligned_t<I>, T>() const
        requires (!std::same_as<I, unaligned_t<I>>)
      {
        return unaligned();
      }

      EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, converting_iterator<I, T> self)
      {
        return eve::convert(eve::read(self.base), eve::as<T>{});
      }

      EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::write_, converting_iterator<I, T> self, T v)
      {
        eve::write(self.base, eve::convert(v, eve::as<value_type_t<I>>{}));
      }

      EVE_FORCEINLINE friend bool operator==(converting_iterator<I, T> const & x, converting_iterator<I, T> const & y)
      {
        return x.base == y.base;
      }

      EVE_FORCEINLINE friend bool operator==(converting_iterator<I, T> const & x, converting_iterator<unaligned_t<I>, T> const & y)
        requires (!std::same_as<I, unaligned_t<I>>)
      {
        return x.base == y.base;
      }

      EVE_FORCEINLINE friend auto operator<=>(converting_iterator<I, T> const & x, converting_iterator<I, T> const & y)
      {
        return spaceship_helper(x.base, y.base);
      }

      EVE_FORCEINLINE friend auto operator<=>(converting_iterator<I, T> const & x, converting_iterator<unaligned_t<I>, T> const & y)
        requires (!std::same_as<I, unaligned_t<I>>)
      {
        return spaceship_helper(x.base, y.base);
      }

      EVE_FORCEINLINE friend auto& operator+=(converting_iterator<I, T>& x, std::ptrdiff_t n)
      {
        x.base += n;
        return x;
      }

      EVE_FORCEINLINE friend std::ptrdiff_t operator-(converting_iterator<I, T> const& x, converting_iterator<I, T> const& y)
      {
        return x.base - y.base;
      }

      EVE_FORCEINLINE friend std::ptrdiff_t operator-(converting_iterator<I, T> const& x, converting_iterator<unaligned_t<I>, T> const& y)
        requires (!std::same_as<I, unaligned_t<I>>)
      {
        return x.base - y.base;
      }
    };
  }

  template <typename I, typename T>
  struct converting_iterator : detail::converting_iterator_common<I, T>
  {
    using _base_t = detail::converting_iterator_common<I, T>;
    using _base_t::_base_t;

    template <typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr,
     converting_iterator<I, T> self, converting_iterator<I, T> other)
    {
      return preprocess_range(tr, convert(as_range(self.base, other.base), as<T>{}));
    }

    template <typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                converting_iterator<I, T> self,
                                converting_iterator<unaligned_t<I>, T> other)
      requires (!std::same_as<I, unaligned_t<I>>)
    {
      return preprocess_range(tr, convert(as_range(self.base, other.base), as<T>{}));
    }
  };

  template <iterator I, typename T>
  struct converting_iterator<I, T> : detail::converting_iterator_common<I, T>
  {
    using _base_t = detail::converting_iterator_common<I, T>;

    using cardinal = typename I::cardinal;
    using wide_value_type = eve::wide<T, cardinal>;

    using _base_t::_base_t;

    converting_iterator<unaligned_t<I>, T> unaligned() const { return *this; }
    EVE_FORCEINLINE auto previous_partially_aligned() const
    {
      return converting_iterator<partially_aligned_t<I>, T>{this->base.previous_partially_aligned()};
    }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
    {
      auto new_base = this->base.cardinal_cast(N);
      return converting_iterator<decltype(new_base), T>{new_base};
    }

    template< relative_conditional_expr C, decorator S, typename Pack>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
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
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C c, wide_value_type v, converting_iterator self )
    {
      auto c1 = map_alternative(
        c,
        [](auto alt) { return eve::convert(alt, eve::as<typename I::value_type>{}); }
      );

      eve::store[c1](eve::convert(v, eve::as<typename I::value_type>{}), self.base);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wide_value_type v, converting_iterator self )
    {
      eve::store(eve::convert(v, eve::as<typename I::value_type>{}), self.base);
    }

    template <relative_conditional_expr C, decorator Decorator, typename U>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(eve::tag::compress_store_,
      C c, Decorator d, wide_value_type v,
      eve::logical<eve::wide<U, cardinal>> m,
      converting_iterator self )
    {
      // No alternative support in compress_store
      auto raw_res = d(eve::compress_store[c])(eve::convert(v, eve::as<typename I::value_type>{}), m, self.base);
      return unaligned_t<converting_iterator>{raw_res};
    }
  };
}

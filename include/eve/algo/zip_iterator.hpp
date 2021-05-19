//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <eve/detail/kumi.hpp>

#include <concepts>
#include <compare>

namespace eve::algo
{
  template <typename I, typename ... Is>
    requires (std::same_as<typename I::cardinal, typename Is::cardinal> && ...)
  struct zip_iterator : operations_with_distance
  {
    using cardinal = typename I::cardinal;
    using storage_type = kumi::tuple<I, Is...>;

    // tuple opt in
    using is_product_type = void;
    static constexpr std::size_t size() noexcept {
      return storage_type::size();
    }

    template <std::size_t idx, typename Self>
      requires std::same_as<zip_iterator, std::remove_cvref_t<Self>>
    friend decltype(auto) get(Self&& self) { return get<idx>(std::forward<Self>(self).storage); }
    // tuple opt in

    zip_iterator() = default;

    explicit zip_iterator(kumi::tuple<I, Is...> x) : storage(x) {}

    explicit zip_iterator(I i, Is ... is) : storage{i, is...} {}

    auto unaligned() const {
      return zip_iterator<unaligned_t<I>, unaligned_t<Is> ...> {
        kumi::map([](auto x) { return x.unaligned(); }, *this)
      };
    }

    zip_iterator& operator+=(std::ptrdiff_t n)
    {
      kumi::for_each([n](auto& x) { x += n; }, *this);
      return *this;
    }

    template <same_unaligned_iterator<zip_iterator> U>
    friend std::ptrdiff_t operator-(zip_iterator x, U y)
    {
      return get<0>(x) - get<0>(y);
    }

    template <same_unaligned_iterator<zip_iterator> U> auto operator==(U x) const
    {
      return get<0>(*this) == get<0>(x);
    }

    template <same_unaligned_iterator<zip_iterator> U>
    auto operator<=>(U x) const { return get<0>(*this) <=> get<0>(x); }

    template <relative_conditional_expr C>
    friend auto tagged_dispatch( eve::tag::load_, C cond, zip_iterator self )
    {
      return kumi::map( [&](auto x) { return eve::load[cond](x); }, self);
    }

    friend auto tagged_dispatch( eve::tag::load_, zip_iterator self )
    {
      return kumi::map( eve::load, self);
    }

    template <relative_conditional_expr C>
    friend auto tagged_dispatch(eve::tag::store_, C cond, auto v, zip_iterator self)
    {
      kumi::map(
        [&](auto _v, auto _it){ eve::store[cond](_v, _it); return 0; },
        v, self
      );
    }

    friend void tagged_dispatch( eve::tag::store_, auto v, zip_iterator self )
    {
      kumi::map(
        [&](auto _v, auto _it){ eve::store(_v, _it); return 0; },
        v, self
      );
    }

    storage_type storage;
  };
}

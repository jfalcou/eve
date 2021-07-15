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

namespace eve::algo {
  template <typename I, typename ... Is>
  struct zip_iterator : operations_with_distance
  {
    using cardinal = typename I::cardinal;
    using value_type = kumi::tuple<typename I::value_type>;
    using wide_value_type = eve::wide<value_type, cardinal>;

    using tuple_type = kumi::tuple<I, Is...>;

    static_assert((std::same_as<cardinal, typename Is::cardinal> && ...));

    // tuple opt in
    using is_product_type = void;
    static constexpr std::size_t size() noexcept {
      return tuple_type::size();
    }

    template <std::size_t idx, typename Self>
      requires std::same_as<zip_iterator, std::remove_cvref_t<Self>>
    friend decltype(auto) get(Self&& self) { return get<idx>(std::forward<Self>(self).storage); }
    // ~tuple opt in

    zip_iterator() = default;

    explicit zip_iterator(tuple_type const& x) : storage(x) {}

    explicit zip_iterator(I i, Is ... is)
      : storage{i, is...}
    {}

    auto unaligned() const
    {
      return zip_iterator<unaligned_t<I>, unaligned_t<Is>...> {
        kumi::map([](auto x) { return x.unaligned(); }, storage)
      };
    }

    auto previous_partially_aligned() const
    {
      // FIX-#809: always aligned support
      if constexpr ((partially_aligned_iterator<I> || ... || partially_aligned_iterator<Is> )) return *this;
      else
      {
        using res_t = zip_iterator<partially_aligned_t<I>, Is...>;

        auto partially_aligned_first = get<0>(storage).previous_partially_aligned();
        std::ptrdiff_t offset = get<0>(storage) - partially_aligned_first;

        res_t res;
        get<0>(res.storage) = partially_aligned_first;

        [&]<std::size_t... idx>(std::index_sequence<idx...>)
        {
          ((get<idx + 1>(res.storage) = get<idx + 1>(storage) - offset), ...);
        }(std::index_sequence_for<Is...>{});

        return res;
      }
    }

    template< relative_conditional_expr C, decorator S>
    friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s, auto pack, zip_iterator self )
    {
      // @Joel: please make this work
      return eve::load(c, s, pack, self.storage);
    }

    tuple_type storage;
  };

}  // namespace eve::algo

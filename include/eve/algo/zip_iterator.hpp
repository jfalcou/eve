//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <eve/detail/kumi.hpp>

#include <concepts>

namespace eve::algo
{
  template <typename ...Is>
  struct  zip_iterator;

  namespace detail
  {
    template<typename... Is> struct zip_iterator_common;

    template<typename... Is>
    std::true_type derived_from_zip_iterator_common_impl(zip_iterator_common<Is...> const &);

    std::false_type derived_from_zip_iterator_common_impl(...);

    template<typename U>
    concept derived_from_zip_iterator_common =
        decltype(derived_from_zip_iterator_common_impl(std::declval<U>()))::value;

    template<typename... Is> struct zip_iterator_common : operations_with_distance
    {
      using value_type = kumi::tuple<typename pointer_traits<Is>::value_type...>;
      using tuple_type = kumi::tuple<Is...>;

      // tuple opt in
      using is_product_type = void;

      template<std::size_t idx, typename Self>
      requires std::derived_from<std::remove_cvref_t<Self>, zip_iterator_common<Is...>>
      friend decltype(auto) get(Self &&self) { return get<idx>(std::forward<Self>(self).storage); }
      // ~tuple opt in

      zip_iterator_common() = default;

      explicit zip_iterator_common(tuple_type const &x) : storage(x) {}

      explicit zip_iterator_common(Is... is) : storage {is...} {}

      auto operator*() const
      {
        using res_t = kumi::tuple<decltype(*std::declval<Is>())...>;
        return [&]<std::size_t... idx>(std::index_sequence<idx...>)
        {
          return res_t {*get<idx>(*this)...};
        }
        (std::index_sequence_for<Is...> {});
      }

      operator zip_iterator<unaligned_t<Is>...>() const
      {
        return zip_iterator<unaligned_t<Is>...> {
            kumi::map([](auto x) { return unalign(x); }, *this)};
      }

      auto unaligned() const { return zip_iterator<unaligned_t<Is>...>(*this); }

      template<typename... Is2>
      friend bool operator==(zip_iterator_common const &x, zip_iterator_common<Is2...> const &y)
      {
        return get<0>(x) == get<0>(y);
      }

      template<typename... Is2> auto operator<=>(zip_iterator_common<Is2...> const &x) const
      {
        return get<0>(*this) <=> get<0>(x);
      }

      template<typename Self>
      requires std::derived_from<std::remove_cvref_t<Self>, zip_iterator_common<Is...>>
      friend Self &operator+=(Self &x, std::ptrdiff_t n)
      {
        kumi::for_each([&](auto &m) { m += n; }, x);
        return x;
      }

      template<typename... Is2> std::ptrdiff_t operator-(zip_iterator_common<Is2...> const &x) const
      {
        return get<0>(*this) - get<0>(x);
      }

      tuple_type storage;
    };
  }

  template <typename ... Is>
  struct zip_iterator : detail::zip_iterator_common<Is...>
  {
    using base = detail::zip_iterator_common<Is...>;
    using base::base;
  };

  template <iterator I, iterator ... Is>
  struct zip_iterator<I, Is...> : detail::zip_iterator_common<I, Is...>
  {
    using base = detail::zip_iterator_common<I, Is...>;
    using cardinal = typename I::cardinal;
    using wide_value_type = eve::wide<typename base::value_type, cardinal>;

    static_assert((std::same_as<cardinal, typename Is::cardinal> && ...));

    using base::base;

    auto previous_partially_aligned() const
    {
      // FIX-#809: always aligned support
      if constexpr ((partially_aligned_iterator<I> || ... || partially_aligned_iterator<Is> )) return *this;
      else
      {
        using res_t = zip_iterator<partially_aligned_t<I>, Is...>;

        auto partially_aligned_first = get<0>(*this).previous_partially_aligned();
        std::ptrdiff_t offset = get<0>(*this) - partially_aligned_first;

        res_t res;
        get<0>(res) = partially_aligned_first;

        [&]<std::size_t... idx>(std::index_sequence<idx...>)
        {
          ((get<idx + 1>(res) = get<idx + 1>(*this) - offset), ...);
        }(std::index_sequence_for<Is...>{});

        return res;
      }
    }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal N) const
    {
      return zip_iterator<decltype(I{}.cardinal_cast(N)), decltype(Is{}.cardinal_cast(N))...> {
        kumi::map([&](auto x) { return x.cardinal_cast(N); }, *this)
      };
    }

    template< relative_conditional_expr C, decorator S>
    friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , auto const& pack, zip_iterator self
                                )
    {
      return eve::load(c, s, pack, self.storage);
    }

    template <relative_conditional_expr C>
    friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type v, zip_iterator self )
    {
      eve::store[cond](v, self.storage);
    }

    friend void tagged_dispatch( eve::tag::store_, wide_value_type v, zip_iterator self )
    {
      eve::store(v, self.storage);
    }
  };

  template <typename ...Is>
  zip_iterator(Is ... is) -> zip_iterator<Is...>;
}  // namespace eve::algo

// tuple opt in
namespace std
{
  template<std::size_t I, eve::algo::detail::derived_from_zip_iterator_common U>
  struct  tuple_element<I, U> : tuple_element<I, typename U::tuple_type>
  {
  };

  template<eve::algo::detail::derived_from_zip_iterator_common U>
  struct tuple_size<U> : std::tuple_size<typename U::tuple_type>
  {
  };
}
// ~tuple opt in

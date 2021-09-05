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
#include <eve/algo/preprocess_range.hpp>

#include <eve/algo/detail/preprocess_zip_range.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <eve/detail/kumi.hpp>

#include <concepts>

namespace eve::algo
{
  template <typename ...Is>
  struct zip_iterator;

  namespace detail
  {
    template <typename, typename>
    struct compatible_zip_iterators_impl : std::false_type {};

    template <typename ...Is1, typename ...Is2>
      requires (sizeof...(Is1) == sizeof...(Is2))
    struct compatible_zip_iterators_impl<zip_iterator<Is1...>, zip_iterator<Is2...>>
    {
      static constexpr bool value = (std::equality_comparable_with<Is1, Is2> && ...);
    };
  }


  template <typename T, typename U>
  concept compatible_zip_iterators = detail::compatible_zip_iterators_impl<T, U>::value;

  namespace detail
  {
    template<typename... Is> struct zip_iterator_common;

    template<typename... Is>
    std::true_type derived_from_zip_iterator_common_impl(zip_iterator_common<Is...> const &);

    std::false_type derived_from_zip_iterator_common_impl(...);

    template<typename U>
    concept derived_from_zip_iterator_common =
        decltype(derived_from_zip_iterator_common_impl(std::declval<U>()))::value;

    template<typename... Is>
    struct zip_iterator_common : operations_with_distance
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

      EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, zip_iterator<Is...> self)
      {
        return kumi::map(eve::read, self.storage);
      }

      EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::write_, zip_iterator<Is...> self, value_type v)
      {
        kumi::for_each(eve::write, self.storage, v);
      }

      operator zip_iterator<unaligned_t<Is>...>() const
      {
        return zip_iterator<unaligned_t<Is>...> {
            kumi::map([](auto x) { return unalign(x); }, *this)};
      }

      auto unaligned() const { return zip_iterator<unaligned_t<Is>...>(*this); }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      friend bool operator==(Self const &x, Other const &y)
      {
        return get<0>(x) == get<0>(y);
      }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      friend auto operator<=>(Self const& x, Other const &y)
      {
        return spaceship_helper(get<0>(x), get<0>(y));
      }

      template<std::derived_from<zip_iterator_common> Self>
      friend Self &operator+=(Self &x, std::ptrdiff_t n)
      {
        kumi::for_each([&](auto &m) { m += n; }, x);
        return x;
      }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      friend std::ptrdiff_t operator-(Self const& x, Other const& y)
      {
        return get<0>(x) - get<0>(y);
      }

      template<typename Traits, std::derived_from<zip_iterator_common> Self,
               std::equality_comparable_with<std::tuple_element_t<0, tuple_type>> S>
      friend auto tagged_dispatch(preprocess_range_, Traits traits, Self self, S l)
      {
        std::ptrdiff_t distance = l - get<0>(self);

        auto map_one_it = [&]<std::size_t idx>(auto f, std::integral_constant<std::size_t, idx>)
        {
          if constexpr (idx == 0) return l;
          else                    return unalign(f) + distance;
        };

        auto real_l =[&]<std::size_t ... idxs>(std::index_sequence<idxs...>) {
          return zip_iterator{ map_one_it(get<idxs>(self), std::integral_constant<std::size_t, idxs>{}) ... };
        }(std::index_sequence_for<Is...>{});

        return preprocess_range(traits, self, real_l);
      }

      tuple_type storage;
    };
  }

  template <typename ... Is>
  struct zip_iterator : detail::zip_iterator_common<Is...>
  {
    using base = detail::zip_iterator_common<Is...>;
    using base::base;

    template<typename Traits, compatible_zip_iterators<zip_iterator<Is...>> Other>
    friend auto tagged_dispatch(preprocess_range_, Traits traits, zip_iterator<Is...> self, Other other)
    {
      auto ranges = kumi::map([](auto f_, auto l_) {
        return as_range(f_, l_);
      }, self, other);

      return detail::preprocess_zip_range(traits, ranges);
    }
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
        get<0>(res.storage) = partially_aligned_first;

        [&]<std::size_t... idx>(std::index_sequence<idx...>)
        {
          ((kumi::get<idx + 1>(res.storage) = kumi::get<idx + 1>(this->storage) - offset), ...);
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
  zip_iterator(kumi::tuple<Is...>) -> zip_iterator<Is...>;

  template <typename ...Is>
  zip_iterator(Is ... ) -> zip_iterator<Is...>;
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

  // I'm so not sure I'm doing this right
  template< typename ...Is, typename ZipI2, template<class> class TQual, template<class> class UQual >
    requires eve::algo::compatible_zip_iterators<eve::algo::zip_iterator<Is...>, ZipI2>
  struct basic_common_reference<eve::algo::zip_iterator<Is...>, ZipI2, TQual, UQual>
  {
    using type = eve::algo::unaligned_t<ZipI2>;
  };
}
// ~tuple opt in

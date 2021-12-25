//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/concepts/types_to_consider.hpp>
#include <eve/algo/concepts/iterator_cardinal.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/preprocess_range.hpp>

#include <eve/algo/views/detail/preprocess_zip_range.hpp>

#include <eve/function/compress_store.hpp>
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <eve/detail/kumi.hpp>

#include <array>
#include <concepts>

namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!    @struct zip_iterator
  //!    @brief  A `relaxed_iterator` on top of multiple `relaxed_iterator`.
  //!            If all of the components are `iterator` they have to have the same cardinal
  //!            and the `zip_iterator` will model `iterator`.
  //!            Should probably never be created directly, use `zip`.
  //!
  //!    **Required header:** `#include <eve/algo/views/zip.hpp>`
  //!
  //!    Has a shorthand `eve::views::zip_iterator` in `<eve/views/zip.hpp>`.
  //! @}
  //================================================================================================

  template <typename ...Is>
  struct zip_iterator;

  namespace detail
  {
    // Don't take always aligned if possible.
    // Prefer aligned if avaliable.
    template <typename ...I>
    constexpr std::size_t main_iterator()
    {
      std::array is_aligned        { partially_aligned_iterator<I> ... };
      std::array is_always_aligned { always_aligned_iterator<I> ... };

      std::size_t res = 0;
      bool is_selected_always_aligned = is_always_aligned[0];

      for (std::size_t i = 0; i != is_aligned.size(); ++i) {
        if (is_always_aligned[i]) { continue; }
        if (is_selected_always_aligned) {
          res = i;
          is_selected_always_aligned = false;
        }
        if (is_aligned[i])
        {
          res = i;
          break;
        }
      }

      return res;
    }

    template <typename, typename>
    struct compatible_zip_iterators_impl : std::false_type {};

    template <typename ...Is1, typename ...Is2>
      requires (sizeof...(Is1) == sizeof...(Is2))
    struct compatible_zip_iterators_impl<zip_iterator<Is1...>, zip_iterator<Is2...>>
    {
      static constexpr bool value = (std::equality_comparable_with<Is1, Is2> && ...);
    };

    template <typename Self, typename T>
    auto convert_zipped(Self self, eve::as<T> tgt);
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
      using value_type        = kumi::tuple<typename pointer_traits<Is>::value_type...>;
      using tuple_type        = kumi::tuple<Is...>;
      using types_to_consider = kumi::result::cat_t<types_to_consider_for_t<Is>...>;

      static constexpr std::size_t main_iterator_idx = detail::main_iterator<Is...>();

      // tuple opt in
      using is_product_type = void;

      template<std::size_t idx, typename Self>
      requires std::derived_from<std::remove_cvref_t<Self>, zip_iterator_common<Is...>>
      friend decltype(auto) get(Self &&self) { return get<idx>(EVE_FWD(self).storage); }
      // ~tuple opt in

      zip_iterator_common() = default;

      explicit zip_iterator_common(tuple_type const &x) : storage(x) {}

      explicit zip_iterator_common(Is... is) : storage {is...} {}

      template <typename ...I1s>
        requires (std::convertible_to<I1s, Is> && ...)
      zip_iterator_common(zip_iterator<I1s...> x)
      {
        storage = kumi::map([]<typename I1, typename I>(I1 from, I) -> I { return from; },
                            x.storage,
                            storage);
      }

      EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, zip_iterator<Is...> self)
      {
        return kumi::map(eve::read, self.storage);
      }

      EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::write_, zip_iterator<Is...> self, value_type v)
      {
        kumi::for_each(eve::write, self.storage, v);
      }

      EVE_FORCEINLINE operator zip_iterator<unaligned_t<Is>...>() const
      {
        return zip_iterator<unaligned_t<Is>...> {
            kumi::map([](auto x) { return unalign(x); }, *this)};
      }

      EVE_FORCEINLINE auto unaligned() const { return zip_iterator<unaligned_t<Is>...>(*this); }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      EVE_FORCEINLINE friend bool operator==(Self const &x, Other const &y)
      {
        return get<main_iterator_idx>(x) == get<main_iterator_idx>(y);
      }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      EVE_FORCEINLINE friend auto operator<=>(Self const& x, Other const &y)
      {
        return spaceship_helper(get<main_iterator_idx>(x), get<main_iterator_idx>(y));
      }

      template<std::derived_from<zip_iterator_common> Self>
      EVE_FORCEINLINE friend Self &operator+=(Self &x, std::ptrdiff_t n)
      {
        kumi::for_each([&](auto &m) { m += n; }, x);
        return x;
      }

      template<std::derived_from<zip_iterator_common> Self, compatible_zip_iterators<Self> Other>
      EVE_FORCEINLINE friend std::ptrdiff_t operator-(Self const& x, Other const& y)
      {
        return get<main_iterator_idx>(x) - get<main_iterator_idx>(y);
      }

      template<typename Traits, std::derived_from<zip_iterator_common> Self,
               std::equality_comparable_with<std::tuple_element_t<0, tuple_type>> S>
      EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits traits, Self self, S l)
      {
        // Here we use 0, zip can be distanced only with first range interface.
        // Main index is for our internal stuff.
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

      template <typename T>
      EVE_FORCEINLINE friend auto tagged_dispatch(convert_, zip_iterator<Is...> self, eve::as<T> tgt)
      {
        return detail::convert_zipped(self, tgt);
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
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits traits, zip_iterator<Is...> self, Other other)
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

    static_assert((std::same_as<iterator_cardinal_t<I>, iterator_cardinal_t<Is>> && ...));

    using base::base;

    EVE_FORCEINLINE auto previous_partially_aligned() const
    {
      if constexpr (partially_aligned_iterator<std::tuple_element_t<base::main_iterator_idx, zip_iterator<I, Is...>>>) return *this;
      else
      {
        // None of the iterators are aligned (while not being always aligned).
        // Otherwise we'd have a different main_iterator_idx.

        auto aligned_main     = get<base::main_iterator_idx>(*this).previous_partially_aligned();
        std::ptrdiff_t offset = get<base::main_iterator_idx>(*this) - aligned_main;

        auto map_one = [&]<std::ptrdiff_t idx>(eve::index_t<idx>) {
          if constexpr( idx == base::main_iterator_idx ) return aligned_main;
          else                                           return get<idx>(*this) - offset;
        };

        return [&]<std::size_t... idxs>(std::index_sequence<idxs...>)
        {
          return zip_iterator<decltype(map_one(eve::index<static_cast<std::ptrdiff_t>(idxs)>))...> {
              map_one(eve::index<static_cast<std::ptrdiff_t>(idxs)>)...};
        }
        (std::index_sequence_for<I, Is...> {});
      }
    }

    EVE_FORCEINLINE auto next_partially_aligned() const
    {
      if constexpr (partially_aligned_iterator<std::tuple_element_t<base::main_iterator_idx, zip_iterator<I, Is...>>>) return *this;
      else
      {
        // None of the iterators are aligned (while not being always aligned).
        // Otherwise we'd have a different main_iterator_idx.

        auto aligned_main     = get<base::main_iterator_idx>(*this).next_partially_aligned();
        std::ptrdiff_t offset = aligned_main - get<base::main_iterator_idx>(*this);

        auto map_one = [&]<std::ptrdiff_t idx>(eve::index_t<idx>) {
          if constexpr( idx == base::main_iterator_idx ) return aligned_main;
          else                                           return get<idx>(*this) + offset;
        };

        return [&]<std::size_t... idxs>(std::index_sequence<idxs...>)
        {
          return zip_iterator<decltype(map_one(eve::index<static_cast<std::ptrdiff_t>(idxs)>))...> {
              map_one(eve::index<static_cast<std::ptrdiff_t>(idxs)>)...};
        }
        (std::index_sequence_for<I, Is...> {});
      }
    }

    static iterator_cardinal_t<I> iterator_cardinal() { return{}; }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
    {
      return zip_iterator<decltype(I{}.cardinal_cast(N)), decltype(Is{}.cardinal_cast(N))...> {
        kumi::map([&](auto x) { return x.cardinal_cast(N); }, *this)
      };
    }

    template< relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , auto const& pack, zip_iterator self
                                )
    {
      return eve::load(c, s, pack, self.storage);
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type_t<zip_iterator> v, zip_iterator self )
    {
      eve::store[cond](v, self.storage);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wide_value_type_t<zip_iterator> v, zip_iterator self )
    {
      eve::store(v, self.storage);
    }

    template <relative_conditional_expr C, decorator Decorator, typename U>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::compress_store_,
      C c, Decorator d, wide_value_type_t<zip_iterator> v,
      eve::logical<eve::wide<U, iterator_cardinal_t<I>>> m,
      zip_iterator self)
    {
      auto raw_res = d(eve::compress_store[c])(v, m, self.storage);
      return unaligned_t<zip_iterator>{raw_res};
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
  template<std::size_t I, eve::algo::views::detail::derived_from_zip_iterator_common U>
  struct  tuple_element<I, U> : tuple_element<I, typename U::tuple_type>
  {
  };

  template<eve::algo::views::detail::derived_from_zip_iterator_common U>
  struct tuple_size<U> : std::tuple_size<typename U::tuple_type>
  {
  };

  // I'm so not sure I'm doing this right
  template< typename ...Is, typename ZipI2, template<class> class TQual, template<class> class UQual >
    requires eve::algo::views::compatible_zip_iterators<eve::algo::views::zip_iterator<Is...>, ZipI2>
  struct basic_common_reference<eve::algo::views::zip_iterator<Is...>, ZipI2, TQual, UQual>
  {
    using type = eve::algo::unaligned_t<ZipI2>;
  };
}
// ~tuple opt in

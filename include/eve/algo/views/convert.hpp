//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/concepts/types_to_consider.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/range_ref.hpp>

#include <eve/traits.hpp>

namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @struct converting_iterator
  //!   @brief An adapter over a `relaxed_iterator` that converts it's values to T.
  //!   Should be created via `convert`.
  //!
  //!    **Required header:** `#include <eve/algo/views/convert.hpp>`
  //!
  //!    Has a shorthand `eve::views::converting_iterator` in `<eve/views/convert.hpp>`.
  //! @}
  //================================================================================================

  template <relaxed_iterator I, typename T>
  struct converting_iterator;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @struct converting_range
  //!   @brief An adapter over a `relaxed_range` that converts it's values to T.
  //!   Should be created via `convert`.
  //!
  //!    **Required header:** `#include <eve/algo/views/convert.hpp>`
  //!
  //!    Has a shorthand `eve::views::converting_range` in `<eve/views/convert.hpp>`.
  //! @}
  //================================================================================================

  template <non_owning_range R, typename T>
  struct converting_range;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @var convert
  //!   @brief Takes an iterator or a range and returns an adapter that has a provided value type.
  //!
  //!  @code{.cpp} eve::algo::views::convert(it_or_r, eve::as<int>{}); @endcode
  //!
  //!  Behaviour for a specific iterator/range can be customized via tagged dispatch:
  //!
  //!  @code{.cpp}
  //!  template <typename T>
  //!  EVE_FORCEINLINE friend auto tagged_dispatch(eve::algo::views::convert_, my_rng self, eve::as<T> tgt);
  //!  @endcode
  //!
  //!    **Required header:** `#include <eve/algo/views/convert.hpp>`
  //!
  //!    Has a shorthand `eve::views::convert` in `<eve/views/convert.hpp>`.
  //! @}
  //================================================================================================


  struct convert_ {
    template<typename Wrapped, typename T>
    auto no_tagged_dispatch(Wrapped &&wrapped, eve::as<T> tgt) const
    {
      if constexpr( relaxed_range<Wrapped> )
      {
        auto rng  = range_ref(EVE_FWD(wrapped));
        using Rng = decltype(rng);

             if constexpr( std::same_as<value_type_t<Rng>, T>               ) return rng;
        else if constexpr( algo::detail::instance_of<Rng, converting_range> ) return (*this)(rng.base, tgt);
        else                                                                  return converting_range<Rng, T> {rng};
      }
      else
      {
        using I = std::remove_cvref_t<Wrapped>;
             if constexpr( std::same_as<value_type_t<I>, T>                  ) return wrapped;
        else if constexpr( algo::detail::instance_of<I, converting_iterator> ) return (*this)(wrapped.base, tgt);
        else                                                                   return converting_iterator<I, T> {wrapped};
      }
    }

    template <typename Wrapped, typename T>
    auto operator()(Wrapped&& wrapped, eve::as<T> tgt) const
    {
      if constexpr (eve::detail::tag_dispatchable<convert_, decltype(EVE_FWD(wrapped)), as<T>>)
      {
        return tagged_dispatch(*this, EVE_FWD(wrapped), tgt);
      }
      else return no_tagged_dispatch( EVE_FWD(wrapped), tgt);
    }
  } inline constexpr convert;

  template <non_owning_range R, typename T>
  struct converting_range
  {
    R base;

    using is_non_owning = void;

    using types_to_consider = kumi::result::cat_t<
      kumi::tuple<T>, types_to_consider_for_t<R>>;

    EVE_FORCEINLINE auto begin() const { return convert(base.begin(), eve::as<T>{}); }
    EVE_FORCEINLINE auto end()   const { return convert(base.end(),   eve::as<T>{}); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, converting_range self)
    {
      auto tr_with_cardinal = default_to(tr, traits {consider_types<T>});
      auto processed        = preprocess_range(tr_with_cardinal, self.base);

      auto ret_tr = drop_key(consider_types_key, processed.traits());

      return preprocess_range_result {
          ret_tr, convert(processed.begin(), as<T>{}), convert(processed.end(), as<T>{})
      };
    }
  };

  template <relaxed_iterator I, typename T>
  struct converting_iterator : operations_with_distance
  {
    I base;
    using value_type = T;
    using types_to_consider = kumi::result::cat_t<kumi::tuple<T>, types_to_consider_for_t<I>>;
    using unaligned_me = converting_iterator<unaligned_t<I>, T>;

    converting_iterator() = default;

    EVE_FORCEINLINE explicit converting_iterator(I base) : base(base) {}

    template <std::convertible_to<I> I1>
    converting_iterator(converting_iterator<I1, T> x) : base(x.base) {}

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::unalign_, converting_iterator self )
    {
      return convert(unalign(self.base), as<T>{});
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, converting_iterator self)
    {
      return eve::convert(eve::read(self.base), eve::as<T>{});
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::write_, T v, converting_iterator self)
    {
      eve::write(eve::convert(v, eve::as<value_type_t<I>>{}),self.base);
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE bool operator==(converting_iterator<I1, T> y) const
    {
      return base == y.base;
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE auto operator<=>(converting_iterator<I1, T> y) const
    {
      return spaceship_helper(base, y.base);
    }

    EVE_FORCEINLINE auto& operator+=(std::ptrdiff_t n)
    {
      base += n;
      return *this;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(converting_iterator const & x, converting_iterator const & y)
    {
      return x.base - y.base;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(converting_iterator const & x, unaligned_me const & y)
      requires (!std::same_as<I, unaligned_t<I>>)
    {
      return x.base - y.base;
    }

    // not eve::iterator

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                converting_iterator f, converting_iterator l)
      requires (!iterator<I>)
    {
      return preprocess_range(tr, convert(as_range(f.base, l.base), as<T>{}));
    }

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                converting_iterator f, unaligned_me l)
      requires (!iterator<I>) && (!std::same_as<I, unaligned_t<I>>)
    {
      return preprocess_range(tr, convert(as_range(f.base, l.base), as<T>{}));
    }

    // eve::iterator -------------
    EVE_FORCEINLINE auto previous_partially_aligned() const
      requires iterator<I>
    {
      return convert(base.previous_partially_aligned(), eve::as<T>{});
    }

    EVE_FORCEINLINE auto next_partially_aligned() const
      requires iterator<I>
    {
      return convert(base.next_partially_aligned(), eve::as<T>{});
    }

    static auto iterator_cardinal() requires iterator<I>
    { return I::iterator_cardinal(); }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
      requires iterator<I>
    {
      return convert(base.cardinal_cast(N), eve::as<T>{});
    }

    template<relative_conditional_expr C, decorator S>
      requires iterator<I>
    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::load_,
                                                C c,
                                                S s,
                                                eve::as<wide_value_type_t<converting_iterator>>,
                                                converting_iterator self)
    {
      auto c1 = map_alternative(
        c,
        [](auto alt) { return eve::convert(alt, eve::as<value_type_t<I>>{}); }
      );

      return eve::convert ( eve::load(c1, s, eve::as<wide_value_type_t<I>>{}, self.base)
                          , eve::as<T>{}
                          );
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::store_equivalent_,
                                                relative_conditional_expr auto c,
                                                wide_value_type_t<converting_iterator> v,
                                                converting_iterator self)
    {
      auto c1 = map_alternative(
        c,
        [](auto alt) { return eve::convert(alt, eve::as<value_type_t<I>>{}); }
      );

      auto v1 = eve::convert(v, eve::as<value_type_t<I>>{});

      return kumi::make_tuple(c1, v1, self.base);
    }
  };
}

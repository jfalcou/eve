//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/concepts/types_to_consider.hpp>
#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/concepts/iterator_cardinal.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/range_ref.hpp>

#include <eve/function/convert.hpp>
#include <eve/function/load.hpp>
#include <eve/function/read.hpp>
#include <eve/function/reverse.hpp>
#include <eve/function/store.hpp>
#include <eve/function/write.hpp>

namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!   @struct reverse_iterator
  //!   @brief An adapter over a `relaxed_iterator` that allows to iterate in the reverse order.
  //!   Should be created by a call to `eve::algo::views::reverse`.
  //!
  //!   NOTE: at this point convert(reverse) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/algo/views/reverse.hpp>`
  //!
  //!    Has a shorthand `eve::views::reverse_iterator` in `<eve/views/reverse.hpp>`.
  //! @}
  //==================

  template <relaxed_iterator I>
  struct reverse_iterator;

  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!   @struct reverse_range
  //!   @brief An adapter over a `reverse_range` that allows to iterate in the reverse order.
  //!   Should be created by a call to `eve::algo::views::reverse`.
  //!   NOTE: at this point convert(reverse) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/algo/views/convert.hpp>`
  //!
  //!    Has a shorthand `eve::views::reverse_range` in `<eve/views/reverse.hpp>`.
  //! @}
  //================================================================================================

  template <non_owning_range R>
  struct reverse_range;

  //================================================================================================
  //! @addtogroup eve.algo.views
  //! @{
  //!   @var reverse
  //!   @brief Takes an iterator or a range and returns an adapter for reverse iteration
  //!
  //!  @code{.cpp} eve::algo::views::reverse(it_or_r); @endcode
  //!
  //!    **Required header:** `#include <eve/algo/views/reverse.hpp>`
  //!
  //!    Has a shorthand `eve::views::reverse` in `<eve/views/reverse.hpp>`.
  //! @}
  //================

  struct reverse_
  {
    template <typename Wrapped>
    auto operator()(Wrapped&& wrapped) const
    {
      if constexpr( relaxed_range<Wrapped> )
      {
        auto rng  = range_ref(EVE_FWD(wrapped));
        using Rng = decltype(rng);

        if constexpr ( algo::detail::instance_of<Rng, reverse_range> ) return rng.base;
        else                                                           return reverse_range<Rng>{rng};
      }
      else
      {
        using I = std::remove_cvref_t<Wrapped>;

        if constexpr ( algo::detail::instance_of<I, reverse_iterator> ) return wrapped.base;
        else                                                            return reverse_iterator<I>{wrapped};
      }
    }
  } reverse;

  template <relaxed_iterator I>
  struct reverse_iterator : operations_with_distance
  {
    using value_type = value_type_t<I>;
    using types_to_consider = types_to_consider_for_t<I>;
    using unaligned_me = reverse_iterator<unaligned_t<I>>;

    I base;

    reverse_iterator() = default;

    EVE_FORCEINLINE explicit reverse_iterator(I base) : base(base) {}

    EVE_FORCEINLINE auto unaligned() const { return reverse(unalign(base)); }
    operator unaligned_me() const { return unaligned(); }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, reverse_iterator self)
    {
      return eve::read(unalign(self.base) - 1);
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::write_, reverse_iterator self, value_type v)
    {
      return eve::write(unalign(self.base) - 1, v);
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE bool operator==(reverse_iterator<I1> y) const
    {
      return base == y.base;
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE auto operator<=>(reverse_iterator<I1> y) const
    {
      return spaceship_helper(y.base, base);
    }

    EVE_FORCEINLINE auto& operator+=(std::ptrdiff_t n)
    {
      base -= n;
      return *this;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(reverse_iterator const & x, reverse_iterator const & y)
    {
      return y.base - x.base;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(reverse_iterator const & x, reverse_iterator const & y)
      requires (!std::same_as<I, unaligned_t<I>>)
    {
      return y.base - x.base;
    }

    // not eve::iterator--------------------
    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                reverse_iterator f, reverse_iterator l)
      requires (!iterator<I>)
    {
      return preprocess_range(tr, reverse(as_range(l.base, f.base)));
    }

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                reverse_iterator f, unaligned_me l)
      requires (!iterator<I>) && (!std::same_as<I, unaligned_t<I>>)
    {
      return preprocess_range(tr, reverse(as_range(l.base, f.base)));
    }

    // eve::iterator -----------------
    EVE_FORCEINLINE auto previous_partially_aligned() const
      requires iterator<I>
    {
      return reverse(base.next_partially_aligned());
    }

    EVE_FORCEINLINE auto next_partially_aligned() const
      requires iterator<I>
    {
      return reverse(base.previous_partially_aligned());
    }

    static auto iterator_cardinal() requires iterator<I>
    { return I::iterator_cardinal(); }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
      requires iterator<I>
    {
      return reverse(base.cardinal_cast(N));
    }

    template<relative_conditional_expr C, decorator S>
      requires iterator<I>
    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::load_,
                                                C                             c,
                                                S                             s,
                                                eve::as<wide_value_type_t<I>> tgt,
                                                reverse_iterator              self)
    {
      return eve::reverse(
        eve::load( eve::reverse_conditional(c, tgt), s, tgt, self.base - iterator_cardinal_v<I>)
      );
    }

    template<relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                C                    c,
                                                wide_value_type_t<I> v,
                                                reverse_iterator     self)
      requires iterator<I>
    {
      eve::store[eve::reverse_conditional(c, eve::as(v))](eve::reverse(v), self.base - iterator_cardinal_v<I>);
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                wide_value_type_t<reverse_iterator> v,
                                                reverse_iterator                    self)
      requires iterator<I>
    {
      eve::store(eve::reverse(v), self.base - iterator_cardinal_v<I>);
    }
  };

  template <non_owning_range R>
  struct reverse_range
  {
    R base;

    using is_non_owning = void;

    using types_to_consider = types_to_consider_for_t<R>;

    EVE_FORCEINLINE auto begin() const { return reverse(base.end()); }
    EVE_FORCEINLINE auto end()   const { return reverse(base.begin()); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, reverse_range self)
    {
      auto processed        = preprocess_range(tr, self.base);

      return preprocess_range_result {
          processed.traits(), reverse(processed.end()), reverse(processed.begin())
      };
    }
  };
}

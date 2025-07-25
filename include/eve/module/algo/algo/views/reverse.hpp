//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/relaxed.hpp>
#include <eve/module/algo/algo/concepts/types_to_consider.hpp>
#include <eve/module/algo/algo/iterator_helpers.hpp>
#include <eve/module/algo/algo/range_ref.hpp>

#include <eve/traits.hpp>

namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @struct reverse_iterator
  //!   @brief An adapter over a `relaxed_iterator` that allows to iterate in the reverse order.
  //!   Should be created by a call to `eve::algo::views::reverse`.
  //!
  //!   NOTE: at this point convert(reverse) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/reverse.hpp>`
  //!
  //!    Has a shorthand `eve::views::reverse_iterator` in `<eve/views/reverse.hpp>`.
  //! @}
  //================================================================================================

  template <relaxed_iterator I>
  struct reverse_iterator;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @struct reverse_range
  //!   @brief An adapter over a `relaxed_range` that allows to iterate in the reverse order.
  //!   Should be created by a call to `eve::algo::views::reverse`.
  //!   NOTE: at this point convert(reverse) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/reverse.hpp>`
  //!
  //!    Has a shorthand `eve::views::reverse_range` in `<eve/views/reverse.hpp>`.
  //! @}
  //================================================================================================

  template <non_owning_range R>
  struct reverse_range;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @var reverse
  //!   @brief Takes an iterator or a range and returns an adapter for reverse iteration
  //!
  //!  @code{.cpp} eve::algo::views::reverse(it_or_r); @endcode
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/reverse.hpp>`
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

        if constexpr ( eve::detail::instance_of<Rng, reverse_range> ) return rng.base;
        else                                                          return reverse_range<Rng>{rng};
      }
      else
      {
        using I = std::remove_cvref_t<Wrapped>;

        if constexpr ( eve::detail::instance_of<I, reverse_iterator> ) return wrapped.base;
        else                                                           return reverse_iterator<I>{wrapped};
      }
    }
  } constexpr reverse;

  template <relaxed_iterator I>
  struct reverse_iterator : operations_with_distance
  {
    using value_type = value_type_t<I>;
    using types_to_consider = types_to_consider_for_t<I>;
    using unaligned_me = reverse_iterator<unaligned_t<I>>;

    I base;

    reverse_iterator() = default;

    EVE_FORCEINLINE explicit reverse_iterator(I b) : base(b) {}

    template <std::convertible_to<I> I1>
    EVE_FORCEINLINE reverse_iterator(reverse_iterator<I1> x) : base(x.base) {}

    EVE_FORCEINLINE auto unalign()  const noexcept { return reverse(eve::unalign(base)); }
    EVE_FORCEINLINE auto read()     const noexcept { return eve::read( eve::unalign(base) - 1);   }

    EVE_FORCEINLINE void write(value_type v) const noexcept { return eve::write(v,eve::unalign(base) - 1); }

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

    template <callable_options O>
    EVE_FORCEINLINE auto load(O const& opts, as<wide_value_type_t<I>> tgt) const
      requires iterator<I>
    {
      auto new_c = eve::reverse_conditional(opts[condition_key], tgt);
      return eve::reverse(eve::load[opts][new_c](base - iterator_cardinal_v<I>, tgt));
    }

    template<callable_options O>
    EVE_FORCEINLINE void store(O const& opts, wide_value_type_t<I> v) const noexcept
      requires iterator<I>
    {
      auto c = opts[condition_key];

      if constexpr (std::same_as<decltype(c), ignore_none_>)
      {
        eve::store(eve::reverse(v), base - iterator_cardinal_v<I>);
      }
      else
      {
        eve::store[eve::reverse_conditional(c, eve::as(v))](eve::reverse(v), base - iterator_cardinal_v<I>);
      }
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

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
  //!   @struct backward_iterator
  //!   @brief An adapter over a `relaxed_iterator` that replaces going forward with going backward.
  //!   For semantic of `reverse` you should use `eve::algo::views::reverse` this is just a helper to do
  //!   backward algorithms.
  //!   Should be created by a call to `eve::algo::views::backward`.
  //!
  //!   NOTE: at this point convert(backward) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/backward.hpp>`
  //!
  //!    Has a shorthand `eve::views::backward_iterator` in `<eve/views/backward.hpp>`.
  //! @}
  //==================

  template <relaxed_iterator I>
  struct backward_iterator;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @struct backward_range
  //!   @brief An adapter over a `relaxed_range` that replaces going forward with going backward.
  //!   For semantic of `reverse` you should use `eve::algo::views::reverse` this is just a helper to do
  //!   backward algorithms.
  //!   Should be created by a call to `eve::algo::views::backward`.
  //!
  //!   NOTE: at this point convert(backward) will not do anything smart.
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/backward.hpp>`
  //!
  //!    Has a shorthand `eve::views::backward_range` in `<eve/views/backward.hpp>`.
  //! @}
  //================================================================================================

  template <non_owning_range R>
  struct backward_range;

    //================================================================================================
  //! @addtogroup views
  //! @{
  //!   @var backward
  //!   @brief Takes an iterator or a range and returns an adapter for backward iteration.
  //!   For semantic of `reverse` you should use `eve::algo::views::reverse` this is just a helper to do
  //!   backward algorithms.
  //!
  //!  @code{.cpp} eve::algo::views::backward(it_or_r); @endcode
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/views/backward.hpp>`
  //!
  //!    Has a shorthand `eve::views::backward` in `<eve/views/backward.hpp>`.
  //! @}
  //================

  struct backward_
  {
    template <typename Wrapped>
    auto operator()(Wrapped&& wrapped) const
    {
      if constexpr( relaxed_range<Wrapped> )
      {
        auto rng  = range_ref(EVE_FWD(wrapped));
        using Rng = decltype(rng);

        if constexpr(eve::detail::instance_of<Rng, backward_range>) return rng.base;
        else                                                        return backward_range<Rng>{rng};
      }
      else
      {
        using I = std::remove_cvref_t<Wrapped>;

        if constexpr(eve::detail::instance_of<I, backward_iterator>)  return wrapped.base;
        else                                                          return backward_iterator<I>{wrapped};
      }
    }
  } constexpr backward;


  template <relaxed_iterator I>
  struct backward_iterator : operations_with_distance
  {
    using value_type = value_type_t<I>;
    using types_to_consider = types_to_consider_for_t<I>;
    using unaligned_me = backward_iterator<unaligned_t<I>>;

    I base;

    backward_iterator() = default;

    EVE_FORCEINLINE explicit backward_iterator(I base) : base(base) {}

    template <std::convertible_to<I> I1>
    EVE_FORCEINLINE backward_iterator(backward_iterator<I1> x) : base(x.base) {}

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::unalign_, backward_iterator self )
    {
      return backward(unalign(self.base));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, backward_iterator self)
    {
      return eve::read(unalign(self.base) - 1);
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::write_, value_type v, backward_iterator self)
    {
      return eve::write(v, unalign(self.base) - 1);
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE bool operator==(backward_iterator<I1> y) const
    {
      return base == y.base;
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE auto operator<=>(backward_iterator<I1> y) const
    {
      return spaceship_helper(y.base, base);
    }

    EVE_FORCEINLINE auto& operator+=(std::ptrdiff_t n)
    {
      base -= n;
      return *this;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(backward_iterator const & x, backward_iterator const & y)
    {
      return y.base - x.base;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(backward_iterator const & x, backward_iterator const & y)
      requires (!std::same_as<I, unaligned_t<I>>)
    {
      return y.base - x.base;
    }

    // not eve::iterator--------------------
    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                backward_iterator f, backward_iterator l)
      requires (!iterator<I>)
    {
      return preprocess_range(tr, backward(as_range(l.base, f.base)));
    }

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr,
                                backward_iterator f, unaligned_me l)
      requires (!iterator<I>) && (!std::same_as<I, unaligned_t<I>>)
    {
      return preprocess_range(tr, backward(as_range(l.base, f.base)));
    }

    // eve::iterator -----------------
    EVE_FORCEINLINE auto previous_partially_aligned() const
      requires iterator<I>
    {
      return backward(base.next_partially_aligned());
    }

    EVE_FORCEINLINE auto next_partially_aligned() const
      requires iterator<I>
    {
      return backward(base.previous_partially_aligned());
    }

    static auto iterator_cardinal() requires iterator<I>
    { return I::iterator_cardinal(); }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
      requires iterator<I>
    {
      return backward(base.cardinal_cast(N));
    }

    template<relative_conditional_expr C, decorator S>
      requires iterator<I>
    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::load_,
                                                C                             c,
                                                S                             s,
                                                eve::as<wide_value_type_t<I>> tgt,
                                                backward_iterator              self)
    {
      return eve::load( eve::reverse_conditional(c, tgt), s, tgt, self.base - iterator_cardinal_v<I>);
    }

    template<relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                C                    c,
                                                wide_value_type_t<I> v,
                                                backward_iterator     self)
      requires iterator<I>
    {
      eve::store[eve::reverse_conditional(c, eve::as(v))](v, self.base - iterator_cardinal_v<I>);
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                wide_value_type_t<backward_iterator> v,
                                                backward_iterator                    self)
      requires iterator<I>
    {
      eve::store(v, self.base - iterator_cardinal_v<I>);
    }
  };

  template <non_owning_range R>
  struct backward_range
  {
    R base;

    using is_non_owning = void;

    using types_to_consider = types_to_consider_for_t<R>;

    EVE_FORCEINLINE auto begin() const { return backward(base.end()); }
    EVE_FORCEINLINE auto end()   const { return backward(base.begin()); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, backward_range self)
    {
      auto processed        = preprocess_range(tr, self.base);

      return preprocess_range_result {
          processed.traits(), backward(processed.end()), backward(processed.begin())
      };
    }
  };

}
